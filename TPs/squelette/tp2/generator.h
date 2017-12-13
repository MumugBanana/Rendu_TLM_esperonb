#include "ensitlm.h"
#include "bus.h"
#include "systemc.h"


SC_MODULE(Generator) {
    ensitlm::initiator_socket<Generator> initiator;
    sc_signal <bool,SC_MANY_WRITERS> irq_signal;
    void processus(void);
    void interrupt(void);
    sc_event irq_received;

    SC_CTOR(Generator);

};
