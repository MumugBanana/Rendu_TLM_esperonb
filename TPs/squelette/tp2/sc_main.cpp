#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "bus.h"
#include "LCDC.h"
#include "systemc.h"
#include "constantes.h"
#include "ROM.h"

int sc_main(int argc, char **argv) {
	(void) argc;
	(void) argv;

	Generator g1("Generator1");
	Bus b("Bus");
	Memory m("Memory", MEM_SIZE);
	LCDC lc("LCDC",sc_time(1.0 / 25, SC_SEC));
	ROM rom("ROM");
	// Connect
	g1.initiator.bind(b.target);
	b.initiator.bind(m.target);
	lc.initiator_socket.bind(b.target);
	lc.target_socket.bind(b.initiator);
	lc.display_int.bind(g1.irq_signal);
	// rom.socket.bind(b.target);
	b.initiator.bind(rom.socket);
	
	// Map memory
	b.map(m.target, MEM_START, MEM_SIZE);
	b.map(lc.target_socket, VIDEO_START, VIDEO_SIZE);
	b.map(rom.socket, ROM_START, ROM_SIZE);

	// Start simu
	sc_core::sc_start();
	return 0;
}
