SYSTEM BUS Test Suite 수행방법

1. 먼저 쉘을 3개를 띄운다.

2. 버스를 띄운다. 9999포트로 띄운다.
   BUS-TCPC-TCPD-TCPC localhost 9999 

3. 이후 다른 쉘에서 SB-TS.sh 를 실행시킨다.
   SB-TS.sh
   이렇게 하면 register ok 메시지가 떨어지게 된다.
   이과정에서는 4가지 상황에 대한 키를 등록하게 되는 과정을 거치게 되는데
   1) k1, *  2) *, k2  3) k1, k2   4) *.*
   이렇게 4가지 상황에 따른 consumer를 BUS에 등록한다.

4. 마지막으로 다른 쉘에서 TPA를 실행시킨다.
   TPA localhost 9999
   이 과정에서는 위에서 등록했던 4가지 상황에 대하여 각각 메세지를 보내게 되고
   그값에 따른 결과물을 횟수로 출력하게 된다.

5. 이후 약간의 시간을 기다리게 되면 SB-TS.sh 에서는 Performance Test를
   수행하게 되고 1초에 10000번의 메세지를 받는 시간을 출력하게 된다.

