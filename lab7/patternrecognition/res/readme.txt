/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150       0.012s            0.003
    200       0.033s            0.010
    300       0.107s            0.014
    400       0.237s            0.025
    800       1.8s              0.103
   1600       13.994            0.388
   3200        110-                 1.495
   6400        10400  -               5.936
  12800       1.2*10^7   -               24.052


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: N^4: fyra nästlade for loopar där 

Sortering: N^2logN
