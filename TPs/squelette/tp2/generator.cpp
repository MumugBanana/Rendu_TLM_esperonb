#include "generator.h"
#include "constantes.h"
#include "LCDC_registermap.h"
#include "LCDC.h"
using namespace std;

void Generator::processus(void) {
	initiator.write(VIDEO_START+LCDC_START_REG, 0x1);
	initiator.write(VIDEO_START+LCDC_ADDR_REG, MEM_START);
	int line_defil = 0;
	uint32_t mask = 0x00000000;
	while(true)
	{
		// Pour faire défiler les lignes, on décale a chaque boucle les pixels
		// d'un distance d'adresse de une ligne, donc la largeur de l'écran
		line_defil+=LCDC::kWidth;
		// Le masque de couleur va aller de 0x00000000 a 0xffffffff par incréments
		// de 0x11111111
		mask >= 0xffffffff ? mask = 0x00000000 : mask = mask + 0x11111111;
		for (uint32_t i = 0; i < ROM_SIZE_IN_PIXEL_LINE; i++) {

				ensitlm::addr_t read_addr = ROM_START + 4*i;
				// Pour faire le décalage, on oublie pas le modulo IMG_SIZE pour ne pas
				// sortir de la mémoire
				ensitlm::addr_t write_addr = MEM_START + ((8*i+ line_defil) % IMG_SIZE);

				ensitlm::data_t rom_data;
				ensitlm::data_t rom_data_part1 = 0x00000000;
				ensitlm::data_t rom_data_part2 = 0x00000000;

				initiator.read(read_addr,rom_data);

				// Decoupage et Repositionnement des valeurs nécéssaires pour les pixels
				rom_data_part1 += (rom_data & 0xF0000000) | \
				 									(rom_data & 0x0F000000) >> 4 | \
													(rom_data & 0x00F00000) >> 8 | \
													(rom_data & 0x000F0000) >> 12;
				rom_data_part2 += (rom_data & 0x0000F000) << 16 | \
												  (rom_data & 0x00000F00) << 12 | \
													(rom_data & 0x000000F0) << 8 | \
													(rom_data & 0x0000000F) << 4;

				// Mise en place du masque de couleurs
				rom_data_part1 = rom_data_part1 | mask;
				rom_data_part2 = rom_data_part2 | mask;

				initiator.write(write_addr, rom_data_part1);
				initiator.write(write_addr+4, rom_data_part2);

		}
		wait(irq_received);
		// Pour eviter de clignoter et de descendre trop vite !
		wait(500, SC_MS);
		// On acquitte les interruptions
		initiator.write(VIDEO_START+LCDC_INT_REG, 0x0);

	}

}

Generator::Generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
    SC_THREAD(processus);

		sc_event irq_received;

		SC_METHOD(interrupt);
		sensitive << irq_signal.posedge_event();
}

void Generator::interrupt(void)
{
		cout << "Generator has received an interruption" << endl;
		irq_received.notify();
}
