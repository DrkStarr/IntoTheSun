
! ---------------------------------------------------------------------------- !
!       COMPUTER ROOM. 11/16/21
!
  Room    computerRoom
   with   short_name [;
              if (computerRoomChair.playerSit == false) {
                  print "Computer Room - Deck A";
                  rtrue;
              }
              print "Computer Room - Deck A ";
              style roman;
              print "(on the chair)";
              rtrue;
          ],
   with   description [;
              if (self.roomCount) {
                  self.roomCount = false;
                  iRoom++;
              }
              if (self.firstTime) {
                  self.firstTime = false;
              } else {
                  player.advanceGravity = false;
              }
              player.inCorridor = false;
              print "It's a strange design, but the room is shaped like a hexagon - with the upper and lower
              portion slanted at a 45-degree angle. In the center is a chair where you have access to a keyboard. ";
              if (self.terminalHasPower) print "The terminal has unusual input, and sits under a central monitor. ";
              else print "The monitor on top of the terminal is blank. The brains of the ship now gone. ";
              if (computerRoomPanel.hasOpen) print "The access panel on the lower aft side is open";
              else print "An access panel on the lower aft side is recessed into the terminal";
              ".^^Behind the chair, there's the hatch that you broke. It will allow you to exit port.";
          ],
          w_to [;
              <<Enter computerRoomHatch>>;
          ],
          u_to [;
              if (computerRoomChair.playerSit) <<GetOff computerRoomChair>>;
          ],
          cant_go [;
              "You can exit port.";
          ],
          before [;
              Exit:
                  if (computerRoomChair.playerSit) <<GetOff computerRoomChair>>;
                  self.firstTime = true;
                  PlayerTo(bridge, 2);
                  rtrue;
              Listen:

              SitRoom:
                  <<Enter computerRoomChair>>;
          ],
          terminalHasPower true,
          roomCount true,
          firstTime true;

! 11/16/21

  RoomObj -> computerRoomObj "room"
    with  name 'quarters' 'area' 'place' 'room' 'section',
          description [;
              <<Look computerRoom>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the room.";
          ];

! 12/29/21

  NoHelp  -> computerRoomChair "chair"
    with  name 'chair' 'seat',
          before [;
              Enter:
                  if (self.playerSit) "You are already sitting down.";
                  self.playerSit = true;
                  "You slip into the chair, pulling yourself up to the keyboard.";
              Examine, Search:
                  player.advanceGravity = false;
                  "The captain sits here when talking to the computer but types in commands using the keyboard. The whole system is old. There's no voice activation here.";
              GetOff:
                  if (self.playerSit) {
                      self.playerSit = false;
                      "Standing up, you get out of the seat.";
                  }
              Take, Remove, Turn, PushDir, Push, Pull:
                  "The chair's not going anywhere.";
          ],
          playerSit false;

! 12/30/21

  NoHelp  -> computerRoomKeyboard "keyboard"
    with  name 'keyboard' 'console' 'terminal',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  if (computerRoomChair.playerSit) "The keyboard sits under the center monitor. There are buttons here with different symbols on them. Some triangles. Others dots.";
                  "You could get a better look at the keyboard if you were sitting down in the chair.";
              Take, Remove, Turn, PushDir, Pull:
                  "The keyboard is part of the console that wraps around the front half of the room. It's part of the ship.";
              SetTo:
                  if (computerRoomChair.playerSit) "There's no numeric input on the keyboard.";
                  "You could get at it if you were sitting down in the chair.";
              Set, SwitchOn:
                  "It doesn't work like that. You would push the keys if you knew what you were doing.";
              Push:
                  <<Push computerRoomKey>>;
          ];

! 12/30/21

  NoHelp  -> computerRoomKey "key"
    with  name 'key' 'button' 'dot' 'triangle' 'symbol' 'pattern' 'group' 'row',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  if (computerRoomChair.playerSit) "You don't recognize any of the patterns, the triangles that are grouped together, or the rows of increasing dots. Though you know this is how you talk to the A.I.";
                  "You could get a better look at it if you were sitting down in the chair.";
              Push:
                  if (computerRoomChair.playerSit) {
                      if (self.keyPushed) "You push again, but the information doesn't change.";
                      self.keyPushed = true;
                      "You push one of the keys. A warning lights up on the center monitor, but it's followed by a garbled message.";
                  }
                  "You could get at it if you were sitting down in the chair.";
              Take, Remove, Turn, PushDir, Pull:
                  "The keyboard is part of the console that wraps around the front half of the room. It's part of the ship.";
              SetTo:
                  if (computerRoomChair.playerSit) "There's no numeric input on the keyboard.";
                  "You could get at it if you were sitting down in the chair.";
              Set, SwitchOn:
                  "It doesn't work like that. You would push the keys if you knew what you were doing.";
          ],
          keyPushed false;

! 03/03/22

  NoHelp  -> computerRoomKeys "keys"
    with  name 'keys' 'dots' 'triangles' 'buttons' 'symbols' 'patterns' 'rows',
          before [;
              Examine, Search:
                  <<Examine computerRoomKey>>;
              Push:
                  <<Push computerRoomKey>>;
              Take, Remove, Turn, PushDir, Pull:
                  <<Take computerRoomKey>>;
              SetTo:
                  <<SetTo computerRoomKey>>;
              Set, SwitchOn:
                  <<Set computerRoomKey>>;
          ],
     has  pluralname;

! 12/30/21

  NoHelp  -> computerRoomMonitor "monitor"
    with  name 'monitor' 'screen' 'information' 'center' 'central' 'garbled' 'message' 'warning',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  if (computerRoomKey.keyPushed && computerRoom.terminalHasPower) {
                      style fixed;
                      print "*** WARNING: STOP DESTRUCT SEQUENCE ***^";
                      print "*** WARNING: STOP DESTRUCT SEQUENCE ***^";
                      print "*** WARNING: STOP DESTRUCT SEQUENCE ***^";
                      AIOutput();
                      style roman;
                      "";
                  }
                  "The monitor is blank like no one is home.";
              Take, Remove, Turn, Push, PushDir, Pull:
                  "The monitor's embedded into the bulkhead. It isn't going anywhere.";
              SetTo, Set:
                  "Try the keyboard, not the monitor.";
              SwitchOn, SwitchOff:
                  "There's no switch. The A.I. controls it.";
          ];

! 12/30/21

  Object  -> computerRoomPanel "panel"
    with  name 'access' 'panel' 'label' 'death' 'high' 'voltage' 'cover',
          before [;
              Close:
                  if (self.hasOpen) "You don't need to do that. You should finish looting the ship.";
                  "The panel is already closed.";
              Examine:
                  player.advanceGravity = false;
                  if (self.hasOpen) {
                      if (coreAI in self) "The panel is open, and the brains of the ship are now at your disposal.";
                      "The panel is open and empty - the main computer now gutted.";
                  }
                  "On the lower aft side of the terminal, there's a label covering the access panel to the core A.I. There are symbols that warn of death and high voltage.";
              Search:
                  if (self.hasOpen) {} else { "You can't see inside, since the panel is closed."; }
              Take, Remove, Turn, Push, PushDir, Pull:
                  "The panel's recessed into the bulkhead and hard to get at.";
              Open:
                  if (self.hasOpen) {
                      if (coreAI in self) "It's already open. You have access to the core A.I.";
                      "It's open, and there's nothing inside - the main computer now gutted.";
                  }
                  if (crowbar in player) {
                      second = crowbar;
                      <<Unlock self second>>;
                  }
                  "You can try to claw at the panel, but you're not going to open it that way.";
              Unlock:
                  if (self.hasOpen) {
                      if (coreAI in self) "It's already open. You have access to the core A.I.";
                      "It's open, and there's nothing inside - the main computer now gutted.";
                  }
                  if (second == sledgehammer) "It might be fun laying into the computer. But a good blow like that would destroy what's inside.";
                  if (second == cattleProd) {
                      if (iCattleProdCharge > 0) "The rod could discharge, and you'd be one step closer to not making it off the ship.";
                      "You poke at the panel, but that does nothing.";
                  }
                  if (second == crowbar) {
                      self.hasOpen = true;
                      give self open;
                      if (crowbar in vortexBag) move crowbar to player;
                      "You reach down, trying to pry open the edge as you work the crowbar back and forth,
                      forcing open the panel. Inside sits the brains of the ship - the core A.I.";
                  }
                  if (second == kabar) {
                      "The ka-bar is a relic, not a tool. It will be worth much more unblemished.";
                  }
                  "You can try to claw at the panel, but you're not going to open it that way.";
              Blow:
                 "You can't blow through your suit. The polymer seals in your environment.";
              Attack, Blow, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                 "That's not going to help.";
              Push, PushDir, Pull, Remove, Rub, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                 "That's not going to help.";
          ],
          hasOpen false,
     has  concealed static container openable ~open;

! 01/07/22

  NoHelp  -> computerRoomComputer "main computer"
    with  name 'main' 'computer' 'mother' 'muthur' 'mu/th/ur',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  print "The computer is built into the bulkhead and has a terminal that wraps around it. On top of the terminal sits a monitor. ";
                  if (computerRoomPanel.hasOpen) {
                      if (coreAI in computerRoomPanel) "The access panel is open and houses the brain for the ship.";
                      "The access panel at the base is open and empty.";
                  }
                  "The access panel at the base is closed.";
              Open:
                  if (crowbar in player) {
                      second = crowbar;
                      <<Unlock computerRoomPanel second>>;
                  }
                  "You can try to claw at the panel, but you're not going to open it that way.";
              Unlock:
                  <<Unlock computerRoomPanel second>>;
              Take, Remove, Turn, Push, PushDir, Pull:
                  "The computer's built into the ship, and it's going nowhere.";
              SetTo, Set:
                  "Try the keyboard, not the computer.";
              SwitchOn, SwitchOff:
                  "There's no switch. The A.I. controls it.";
          ];

! 02/18/22

  NoHelp  -> computerRoomHatch "hatch"
    with  name 'hatch' 'door' 'frame' 'dent' 'dents',
          before [;
              Attack:
                  "You already did that.";
              Examine, Search:
                  player.advanceGravity = false;
                  "You beat on the hatch pretty well. All that's left is a frame, dented and bruised.";
              Enter:
                  if (computerRoomChair.playerSit) {
                      computerRoomChair.playerSit = false;
                      print "(first getting out of the chair)^";
                  }
                  computerRoom.firstTime = true;
                  PlayerTo(bridge, 2);
                  rtrue;
              Open:
                  "You already broke it open.";
          ];

! 05/07/22

  StObj   -> computerRoomLights "lights"
    with  name 'dim' 'light' 'lights' 'glow' 'soft' 'amber' 'led' 'leds' 'orange' 'pale' 'color' 'barely' 'shape' 'shapes' 'strange' 'shifting',
          before [;
              Examine:
                  player.advanceGravity = false;
                  if (coreAI.takenSelf) "All the lights in this room died the moment you removed the core AI.";
                  "Lights line the walls like they are part of the AI and one way it communicates, shifting over time. However, they are barely lit, with the ship running low on power.";
              Go:
                  "You are already here.";
              Read:
                  "There's nothing to read, just strange shapes shifting in front of you.";
          ],
     has  pluralname;
