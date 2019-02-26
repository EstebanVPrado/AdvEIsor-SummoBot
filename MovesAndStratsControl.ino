// -------------------- Start Move --------------------
void startMove() {
  switch (getCodeSwitch()) {
    case 0:
      frontAttack();
      break;
    case 1:
      sideAttackL();
      break;
    case 2:
      sideAttackR();
      break;
    case 3:
      sideAttackAndTurnL();
      break;
    case 4:
      sideAttackAndTurnR();
      break;
    case 5:
      backAwayL();
      break;
    case 6:
      backAwayR();
      break;
    case 7:
      backAwayAndAttackL();
      break;
    case 8:
      backAwayAndAttackR();
      break;
    default:
      frontAttack();
      break;
  }
}

// -------------------- Default Move --------------------
void asUsual() {
  randomSearch();
}
// -------------------- Situational Moves --------------------
void situations() {

  //seekAndStopUS();
  seekAndDestroyIR();
  dontFall(); // MUST be the last function

}

