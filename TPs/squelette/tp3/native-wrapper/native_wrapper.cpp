#include "ensitlm.h"
#include "native_wrapper.h"

/*
 * The C compiler does a bit of magic on the main() function. Trick it
 * by changing the name to something else.
 */
#define main __start

/* extern "C" is needed since the software is compiled in C and
 * is linked against native_wrapper.cpp, which is compiled in C++.
 */
extern "C" int main();
extern "C" void interrupt_handler();

extern "C" void hal_write32(uint32_t addr, uint32_t data) {
	NativeWrapper::get_instance()->hal_write32(addr, data);
}

extern "C" unsigned int hal_read32(uint32_t addr) {
	return NativeWrapper::get_instance()->hal_read32(addr);
}

extern "C" void hal_cpu_relax() {
	NativeWrapper::get_instance()->hal_cpu_relax();
}

extern "C" void hal_wait_for_irq() {
	NativeWrapper::get_instance()->hal_wait_for_irq();
}

/* To keep it simple, the soft wrapper is a singleton, we can
 * call its methods in a simple manner, using
 * NativeWrapper::get_instance()->method_name()
 */
NativeWrapper * NativeWrapper::get_instance() {
	static NativeWrapper * instance = NULL;
	if (!instance)
		instance = new NativeWrapper("native_wrapper");
	return instance;
}

NativeWrapper::NativeWrapper(sc_core::sc_module_name name) : sc_module(name),
							     irq("irq")
{
	abort(); // TODO
}

void NativeWrapper::hal_write32(unsigned int addr, unsigned int data)
{
	tlm::tlm_response_status response = socket.write(addr, data);
	if(response !=  tlm::TLM_OK_RESPONSE) {
		std::cout << "Write error" << response;
	}
}

unsigned int NativeWrapper::hal_read32(unsigned int addr)
{
	data_t result_value;
	tlm::tlm_response_status response = socket.read(addr, result_value);
	if(response !=  tlm::TLM_OK_RESPONSE) {
		std::cout << "Read error" << response;
	}
	return result_value;
}

void NativeWrapper::hal_cpu_relax()
{
	// Attente de temps arbitraire
	SC_WAIT(500, SC_NS);
}

void NativeWrapper::hal_wait_for_irq()
{
	// Attente, puis reset du signal
	if (!interrupt) {
		wait(interrupt_event);
	}
    interrupt = false;
}

void NativeWrapper::compute()
{
	abort(); // TODO
}

void NativeWrapper::interrupt_handler_internal()
{
	abort(); // TODO
}
