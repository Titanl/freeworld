#include "src/sp/sp.hpp"

#include <cstring> //memcpy
#include <string>
#include <stdlib.h> //exit(i)
#include <vector>

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>

#include "src/integration-headers/mpc-sp/input.hpp"
#include "src/integration-headers/mpc-mps-sp/system.hpp"
#include "src/mpc-sp/handle_mi.hpp"
#include "src/mpc-sp/package_manager.hpp"
#include "src/mps-sp/load_vm.hpp"
#include "src/mps-sp/core_utils.hpp"
#include "src/mps-sp/database/database.hpp"

namespace Freeworld {

Freeworld::MiParser miParser;

mrb_state* vm;

void init_mi_parser(mrb_state * vm);
mrb_value parse_mi_func (mrb_state* state, mrb_value value);
void init_ci_poller(mrb_state * vm);
mrb_value poll_ci_func (mrb_state* state, mrb_value value);

void start(std::string world, std::vector<std::string> vm_pkgs, std::vector<std::string> media_pkgs) {
	Freeworld::Integration::start();
	vm = mrb_open();
	Freeworld::init_core_utils(vm);
	Freeworld::init_database(vm);
	init_mi_parser(vm);
	init_ci_poller(vm);
	Freeworld::load_vm(vm, vm_pkgs);
	for (auto iter = media_pkgs.begin(); iter!=media_pkgs.end(); iter++) {
		Freeworld::get_package_manager()->load(*iter);
	}
	//instruct module to start
	mrb_load_string(vm, ("start_instance_sp '" + world + "'").c_str());
}

void stop() {
	mrb_close(vm);
	Freeworld::Integration::stop();
}

void init_mi_parser(mrb_state* vm) {
	struct RClass* parse_mi_class = mrb_define_class(vm, "Graphics", vm->object_class);
	mrb_define_module_function(vm, parse_mi_class, "parse_mi", &parse_mi_func, MRB_ARGS_ARG(1,0));
}

mrb_value parse_mi_func (mrb_state* vm, mrb_value self) {
	mrb_value mi;
	mrb_get_args(vm, "S", &mi);
	int len = RSTRING_LEN(mi);
	uint8_t* data = new uint8_t[len];
	auto mi_ptr = RSTRING_PTR(mi);
	memcpy(data, mi_ptr, len);
	miParser.parse_mi(len, data);
	return mrb_nil_value();
}

void init_ci_poller(mrb_state* vm) {
	struct RClass* poll_ci_class = mrb_define_class(vm, "Control", vm->object_class);
	mrb_define_module_function(vm, poll_ci_class, "poll_ci", &poll_ci_func, MRB_ARGS_ARG(0,0));
}

mrb_value poll_ci_func (mrb_state* vm, mrb_value value) {
	Freeworld::Integration::InputEvent ie;
	if (Freeworld::Integration::poll_input(&ie)) {
		return mrb_str_new(vm, (char*)&ie, 8);
	}
	return mrb_str_new(vm, NULL, 0);
}

} // end of namespace Freeworld
