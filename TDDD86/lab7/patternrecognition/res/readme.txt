/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
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
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: N^4: fyra n�stlade for loopar d�r längden av varje loop är beroende av N.
Uppmärksamma, de inre loopar är kanske inte N, men subtraktion av mindre tal kan 
försummas då dessa har ej betydelse när N är väldigt stort.

Sortering: N^2logN
