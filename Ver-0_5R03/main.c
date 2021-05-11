#include "mod_libs.h"


int main(void) {
    loadBasicSetUp();

    while(-1){
    }
}


#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR_HOOK(void){
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR_HOOK(void){
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR_HOOK(void){
}

#pragma vector=NMI_VECTOR
__interrupt void NMI_ISR_HOOK(void){
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR_HOOK(void){
}
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR_HOOK(void){

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMERA0_ISR_HOOK(void){

}


#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMERA1_ISR_HOOK(void){

}

#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR_HOOK(void){
}
