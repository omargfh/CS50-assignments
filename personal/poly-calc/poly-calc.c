  #include <stdio.h>
  #include <math.h>

  // declare functions
  int navigatorLauncher();
  void productCalc();
  void inputEq();
  void doPowerRule();
  void doProductRule();
  void addLikeTerms();
  void subtractLikeTerms();
  void doMultiplication();
  void printResults();
  void addCalc();
  void subtractCalc();
  void multiplyCalc();
  void processID();

  // initiate global variables
  double coefficientValues[6][100]; // stores coefficients of rational terms
  double powerValues[6][100]; // stores power values of rational terms
  char operandsInput[6][100]; // stores the sign following each term

  /* TEMPLATE FOR PASSING ARRAY AS AN ARGUMENT

  void functionName(double *var1, double *var2, char *var3) {
    // initiate variables
    double coefficientValues[100]; // stores coefficients of rational terms
    double powerValues[100]; // stores power values of rational terms
    char operandsInput[100]; // stores the sign following each term

    // pass arrary
    for(int x=0; x < 100; x++)
    {
        coefficientValues[x] = *var1;
        powerValues[x] = *var2;
        operandsInput[x] = *var3;
        var1++; var2++; var3++;
    }
  */

  // Program Processors
  void inputEq(int processID, int equationID) {
        // take input
        for (int i = 1; i > 0; i++){
            if (i == 1){
                printf("Coefficient of No. %d term: ", i);
            }
            else {
                printf("Positive Coefficient of No. %d term: ", i);
            }
            scanf("%lf", &coefficientValues[equationID][i-1]);
            printf("Power of No. %d term: ", i);
            scanf("%lf", &powerValues[equationID][i-1]);
            printf("Operand of No. %d term (0 for termination): ", i);
            scanf("%c", &operandsInput[equationID][i-1]); // error: it only works when wrote twice (WHY??)
            scanf("%c", &operandsInput[equationID][i-1]);
            if ((int)operandsInput[equationID][i-1] == 48) { //48, ASCII for 0
              break;
            }
            else if ((int)operandsInput[equationID][i-1] != 43 && (int)operandsInput[equationID][i-1] != 45){
              while ((int)operandsInput[equationID][i-1] != 43 && (int)operandsInput[equationID][i-1] != 45 && (int)operandsInput[equationID][i-1] != 48) {
              printf("Repeat operand of No. %d term (0 for termination): ", i);
                scanf("%c", &operandsInput[equationID][i-1]); // error: it only works when wrote twice (WHY??)
              scanf("%c", &operandsInput[equationID][i-1]);
              }; if ((int)operandsInput[equationID][i-1] == 48) {break;} else {continue;}
            }
            else {
              continue;
            }
          };

        // store original values
        for(int x=0;x<100;x++) {
          coefficientValues[equationID+2][x] = coefficientValues[equationID][x];
          powerValues[equationID+2][x] = powerValues[equationID][x];
          operandsInput[equationID+2][x] = operandsInput[equationID][x];
        }
        // debug
        printf("\n%g", coefficientValues[equationID][0]);printf("\n%g, %g", coefficientValues[equationID][0], powerValues[equationID][0]);

        // processID switch
        switch (processID) {
          case 0: break;
          case 100: doPowerRule(100, equationID); break; // only doPowerRule
          case 200: doPowerRule(200, equationID); break; // + addLikeTerms
          case 300: doPowerRule(300, equationID); break; // + printResults
          // case 400: doPowerRule(400); break; // + storeDerivOne
          // case 500: doPowerRule(500); break; // + storeDerivTwo
          default: break;
        }
  }

  void doPowerRule(int processID, int equationID) {
    //debug
    printf("\n%g, %g", coefficientValues[equationID][0], powerValues[equationID][0]);

    // mathematics
    for (int j = 0; j < 100; j++)
        {
          if ((int)operandsInput[equationID][j-1] == 48) {
            break;
          }
          else {
            if (j == 0) {
              coefficientValues[equationID][j] *= powerValues[equationID][j];
              powerValues[equationID][j] = powerValues[equationID][j] - 1;
            }
            else {
              if ((int)operandsInput[equationID][j-1] == 43) {
                coefficientValues[equationID][j] = coefficientValues[equationID][j] * powerValues[equationID][j];
                powerValues[equationID][j] = powerValues[equationID][j] - 1;
              }
              else if ((int)operandsInput[equationID][j-1] == 45) {
                coefficientValues[equationID][j] = coefficientValues[equationID][j] * powerValues[equationID][j] * -1;
                powerValues[equationID][j] = powerValues[equationID][j] - 1;
              }
            }
          }
        }
        //debug
        printf("\n%g, %g", coefficientValues[equationID][0], powerValues[equationID][0]);

        // processID
        switch (processID) {
              case 0: break;
              case 100: break; // only doPowerRule
              case 200: addLikeTerms(200, equationID, 0); break; // only addLikeTerms
              case 300: addLikeTerms(300, equationID, 0); break; // + printResults
              // case 400: addLikeTerms(400); break; // + storeDerivOne
              // case 500: addLikeTerms(500); break; // + storeDerivTwo
              default: break;
        }
  }

  void addLikeTerms(int processID, int equationID, int navID) {

    // addLikeTerms
    for (int checkA = 0; checkA < 100; checkA++) { // adds similar power terms
        for (int checkB = checkA + 1 - navID; checkB < 100; checkB++) {
          if ((int)powerValues[equationID][checkA] == (int)powerValues[equationID + navID][checkB]
              && (int)coefficientValues[equationID][checkA] != 0)
          {

            if ((int)operandsInput[equationID][checkA] == (int)operandsInput[equationID + navID][checkB]
                && (int)operandsInput != 48)
            {

              coefficientValues[equationID][checkA + 1] = (int)coefficientValues[equationID][checkA + 1] + (int)coefficientValues[equationID + navID][checkB + 1];


            }
            else if ((int)operandsInput[equationID][checkA] == 45 || (int)operandsInput[equationID][checkB]== 45)
            {

              coefficientValues[equationID][checkA + 1] = (int)coefficientValues[equationID][checkA + 1] - (int)coefficientValues[equationID + navID][checkB + 1];


            }

            coefficientValues[equationID + navID][checkB] = (int)coefficientValues[equationID + navID][checkB] - (int)coefficientValues[equationID + navID][checkB];


          }
          else
          {

            continue;

          }
        }
      }

    // debug
    printf("\n%g, %g", coefficientValues[equationID][0], powerValues[equationID][0]);

    // processID
    switch (processID) {
              case 0: break;
              case 100: break; // only doPowerRule
              case 200: break; // only addLikeTerms
              case 300: printResults(equationID); break; // only printResults
              // case 400: storeDerivOne(coefficientValues, powerValues, operandsInput); break; // only storeDerivOne
              // case 500: storeDerivTwo(coefficientValues, powerValues, operandsInput); break; // only storeDerivOne
              default: break;
    }
  }

  void subtractLikeTerms(int processID, int equationID, int navID) {
    // addLikeTerms
    for (int checkA = 0; checkA < 100; checkA++) { // adds similar power terms
        for (int checkB = checkA + 1 - navID; checkB < 100; checkB++) {
          if ((int)powerValues[equationID][checkA] == (int)powerValues[equationID + navID][checkB] && (int)coefficientValues[equationID][checkA] != 0) {
            coefficientValues[equationID][checkA] = (int)coefficientValues[equationID][checkA] - (int)coefficientValues[equationID + navID][checkB];
            coefficientValues[equationID + navID][checkB] = (int)coefficientValues[equationID + navID][checkB] - (int)coefficientValues[equationID + navID][checkB];
          }
          else {
            continue;
          }
        }
      }

    // debug
    printf("\n%g, %g", coefficientValues[equationID][0], powerValues[equationID][0]);

    // processID
    switch (processID) {
              case 0: break;
              case 100: break; // only doPowerRule
              case 200: break; // only addLikeTerms
              case 300: printResults(equationID); break; // only printResults
              // case 400: storeDerivOne(coefficientValues, powerValues, operandsInput); break; // only storeDerivOne
              // case 500: storeDerivTwo(coefficientValues, powerValues, operandsInput); break; // only storeDerivOne
              default: break;
    }
  }

  void doMultiplication(int equationID, int equationPointer, int navID) {
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j <10; j++){
        coefficientValues[equationID + navID][10*i+j] = (int)coefficientValues[equationID][i] * (int)coefficientValues[equationID + equationPointer][j];
        powerValues[equationID + navID][10*i+j] = (int)powerValues[equationID][i] + (int)powerValues[equationID + equationPointer][j];
        if ((int)operandsInput[equationID][i] == (int)operandsInput[equationID + equationPointer][j] && (int)operandsInput[equationID][i] == 43) {
          operandsInput[equationID + navID][10*i+j] = operandsInput[equationID + equationPointer][i];
        }
        else if ((int)operandsInput[equationID][i] == (int)operandsInput[equationID + equationPointer][j] && (int)operandsInput[equationID][i] == 45) {
          operandsInput[equationID + navID][10*i+j] = '+';
        }
        else if ((int)operandsInput[equationID][i] != (int)operandsInput[equationID + equationPointer][j]) {
          operandsInput[equationID + navID][10*i+j] = '-';
        }
      }
    }
  }

  void printResults(int equationID) {

    // printResults
    printf("\nYour result is: ");
        for (int k = 0; k < 100; k++) {
          if (k == 0) {
            if ((int)coefficientValues[equationID][k] == 0) {
              continue;
            }
            else if ((int)powerValues[equationID][0] == 0) {
                printf("%g", coefficientValues[equationID][k]);
            }
            else if ((int)powerValues[equationID][0] == 1){
              printf("%gX", coefficientValues[equationID][k]);
            }
            else {
              printf("%gX^%g", coefficientValues[equationID][k], powerValues[equationID][k]);
            }
          }
          else if (k != 0) {
            if ((int)operandsInput[equationID][k-1] == 48) {
              break;
            }
            else if ((int)coefficientValues[equationID][k] == 0) {
              continue;
            }
            else if ((int)operandsInput[equationID][k-1] == 45) {
                if (powerValues[equationID][k] != 0) {
                /*printf("+");*/ printf("%gX^%g", coefficientValues[equationID][k], powerValues[equationID][k]);
                }
                else if (powerValues[equationID][k] == 0) {
                printf("%g", coefficientValues[equationID][k]);
                }
            }
            /*else if ((int)powerValues[equationID][0] == 0) {
                printf("%g", coefficientValues[equationID][k]);
            }*/
            else if ((int)operandsInput[equationID][k-1] == 43) {
                if (powerValues[equationID][k] != 0) {
                printf("+"); printf("%gX^%g", coefficientValues[equationID][k], powerValues[equationID][k]);
                }
                else if (powerValues[equationID][k] == 0) {
                printf("+%g", coefficientValues[equationID][k]);
                }
              }
            }
      }
    // debug
    printf("\n%g", coefficientValues[equationID][0]);
    // printf("\n%g", powerValues[0]);

    // launch Navigator
    navigatorLauncher();


  }



  // Program Screens (Others)
  void helpScreen() {
      printf("\n■ THE HELP GUIDE ■\n");
      printf("■ Whenever you see 'Navigator' showing, it means you can input one of the values mentioned in the home screen to navigate the program");
      navigatorLauncher();
  }

  void powerCalc() {
    printf("\n■ POWER RULE RATIONAL CALCULATOR ■\n\n■ You will now add the terms in order from the leading to the last term\n■ To add a term, you start by adding its positive coefficient (except for the first term, add the whole coefficient), then the power of its variable and the operand that follows it (+ or -)\n■ You may also use the 0 to terminate the addition of newer terms and proceed to the results\n\n■ You will repeat this process twice, once for every equation\n\n ■ MAXIMUM NUMBER OF TERMS PER FUNCTION: 100\n\n");

    inputEq(300, 0);
  }

  void productCalc() {
    printf("\n■ PRODUCT RULE RATIONAL CALCULATOR ■\n\n■ You will now add the terms in order from the leading to the last term\n■ To add a term, you start by adding its positive coefficient (except for the first term, add the whole coefficient), then the power of its variable and the operand that follows it (+ or -)\n■ You may also use the 0 to terminate the addition of newer terms and proceed to the results\n\n■ MAXIMUM NUMBER OF TERMS: 100\n\n");

    inputEq(400, 0);
    inputEq(400, 1);
  }

  void addCalc() {
    inputEq(0, 0);
    inputEq(0, 1);
    addLikeTerms(300, 0, 1);
  }

  void subtractCalc() {
    inputEq(0, 0);
    inputEq(0, 1);
    subtractLikeTerms(300, 0, 1);
  }

  void multiplyCalc() {
    inputEq(0, 0);
    inputEq(0, 1);
    doMultiplication(0, 1, 4);
    addLikeTerms(300, 4, 0);
  }

  void processID() {
    printf("\n\n■ THIS IS A DEVELOPERS GUIDE ■\n\n■ 100: Input a single equation and process its derivative\n■ 200: Input a single equation and find its simplest derivative\n■ 300: Process the derivative of a single function and print its results\n■ 400/500: Find the derivative of a single equation and store it\n■ 600: Input two equations for addition\n■ 700: Input two equations for subtraction\n■ 800: Input two equations for multiplication\n\n");
  }

  // Program Navigation
  int navigatorLauncher() {
      printf("\n\nNavigator: ");
      char inputValue;
      scanf(" %c", &inputValue);
      int numValue = (int)inputValue;

      // Navigation Statements
      switch (numValue) {
        case 48: return 0;
        case 49: addCalc(); break;
        case 50: subtractCalc(); break;
        case 51: multiplyCalc(); break;
        case 52: productCalc(); break;
        case 53: powerCalc(); break;
        case 64: processID(); break;
        case 72: helpScreen(); break;
        case 104: helpScreen(); break;
        default: navigatorLauncher(); break;
      }
      return 0;
  }

  // Program Screens
  void welcomeScreen()
  {
      printf("■ Welcome to The Simple Algebriac Calculator! ■\n\n");
      printf("■ Input a number to navigate the program\n");
      printf("0. Terminate the program\n1. Add two functions\n2. Subtract two functions\n3. Multiply two functions\n4. Find the derivative of a product function\n5. Find the derivative of a polynomial function\nH. Help\n");
      navigatorLauncher();
  }

  // Program Launcher
  int main()
  {
      welcomeScreen();
      return 0;
  }