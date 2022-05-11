! ---------------------------------------------------------------------------- !
!       PLAYER. 10/08/21
!

  Object  SelfPlayer "self"
    with  short_name [; return L__M(##Miscellany, 18); ],
          name 'yourself',
          capacity MAX_CARRIED,
          description [;
              self.advanceGravity = false;
              "Over an average set of clothes, your polymer bodysuit protects you from the elements.
              Sealed in by it, you don't have access to your pockets. Everything will have to go into
              your vortex bag.";
          ],
          each_turn [ oldMonsterDes alienDistance;
              ! ***************************************************
              ! Resets PFX - The xenomorph's faster than that.
              !            - But the xenomorph knows where you are.
              ! ***************************************************
              if (self.xenomorphKnows) {
                  iXenoKnows++;
              }
              if (iXenoKnows > 1) {
                  iXenoKnows = 0;
                  self.xenomorphKnows = false;
              }
              ! ************************************
              ! Sets Whether Player Is Moving Or Not
              ! ************************************
              if (parent(player) == oldPlayerLoc) {
                  self.isMoving = false;
              } else self.isMoving = true;
              oldPlayerLoc = parent(player);

              ! **************************************
              ! Control Time for Meta Verbs like RULES
              ! **************************************
              if (self.advanceTime) {
                  if (self.advanceGravity) {
                      ! ************************
                      ! Deal with Gravity & Time
                      ! ************************
                      iTime = iTime + 1;
                      if (iTime >= iProgressiveGravity) {
                          iTime = 0;
                          iGravityDecimal = iGravityDecimal + 1;
                          if (iGravityDecimal >= 10) {
                              iGravityDecimal = 0;
                              iGravityForce = iGravityForce + 1;
                          }
                          ! ****************
                          ! Death By Gravity
                          ! ****************
                          if (iGravityForce == 9 && iGravityDecimal > 0) {
                              deadflag = 1;
                              self.mentionUndo = false;
                              "^The gravity becomes too strong. You hear the ship begin to strain, metal bending under the force.
                              Even if you made it back to your ship, by the time you settled in and fired up the engines, you wouldn't
                              be able to escape the gravity well. You're trapped and will die in the fiery depths of the sun.";
                          }
                          ! **********************
                          ! Warnings About Gravity
                          ! **********************
                          if (iGravityForce == 3 && self.firstGravityIncrease) {
                              self.firstGravityIncrease = false;
                              iProgressiveGravity = iProgressiveGravity - 1;
                              print "^You feel the sun pull harder on the ship. A deep groan is expelled from the pressure.^";
                          }
                          if (iGravityForce == 5 && self.gravityIncrease) {
                              self.gravityIncrease = false;
                              iProgressiveGravity = iProgressiveGravity - 1;
                              print "^With a sharp crack, the creaking and groaning stops for a moment as something breaks under pressure.^";
                          }
                          if (iGravityForce == 8 && self.gravityWarning) {
                              self.gravityWarning = false;
                              print "^At 8g, you really start to feel it with labored movement and slower reaction speed.
                              You need to get off the ship before she pulls you under.^";
                          }
                      }
                  } else {
                      self.advanceGravity = true;
                  }
                  ! *********************************
                  ! Handle The Alien - Movement & All
                  ! *********************************
                  if (parent(self) == parent(alien)) {
                      self.alienEnterRoom = false;
                      StartDaemon(alien);
                      if (alien.sleeping) {
                          ! *************
                          ! Wake Up Alien
                          ! *************
                          alien.sleeping = false;
                          if (self.inCorridor) print "^You make too much noise stepping into this corridor";
                          else print "^You make too much noise stepping into this room";
                          ", waking a creature that looks like it could kill you with one swipe. He sits there twitching for a second. Slime drips off his face.
                          Then the alien opens his eyes. He shivers for a moment and steps back. Spitting, he reaches out.";
                      } else {
                          ! ****************
                          ! Walk In On Alien
                          ! ****************
                          if (player in bridge) {
                              if (self.inComputerRoom) {
                                  "^The alien, hiding in the ventilation system, sees you. But the drool from his mouth
                                  falls, hitting the deck in front of you and giving you a second to react.";
                              } else {
                                  "^The alien seems to come from out of nowhere. He's quick and silent when looking for his prey. Then, spitting, he hones in on you. His hands reach out.";
                              }
                          }
                          if (self.inCorridor) {
                              if (self.isMoving) {
                                  if (self.firstRanIntoAlien == false) {
                                      self.firstRanIntoAlien = true;
                                      "^You stop in this corridor as you watch an alien slowly crawl out of the ventilation system - he spits at the sight of you. The creature jumps down to the deck, standing as tall as the corridor. You hear a hiss from deep inside the beast before he reaches out at you.";
                                  } else {
                                      "^In this corridor, the alien spits at the sight of you. Taking a step back, he jumps up towards the ventilation system, then stops. You hear a hiss from deep inside the creature before he reaches out at you.";
                                  }
                              }
                              if (self.firstRanIntoAlien == false) {
                                  self.firstRanIntoAlien = true;
                                  "^From above, the alien slowly crawls out of the ventilation system - he spits at the sight of you. The creature jumps down to the deck, standing as tall as the corridor. You hear a hiss from deep inside the beast before he reaches out at you.";
                              } else {
                                  "^The alien seems to come from out of nowhere. He's quick and silent when looking for his prey. Then, spitting, he hones in on you. His hands reach out.";
                              }
                          } else {
                              if (self.isMoving) {
                                  if (self.firstRanIntoAlien == false) {
                                      self.firstRanIntoAlien = true;
                                      "^In the corner, you watch an alien slowly crawl out of the ventilation system - he spits at the sight of you. The creature pushes itself off the deck, standing as tall as the room. You hear a hiss from deep inside the beast before he reaches out at you.";
                                  } else {
                                      "^In the corner of this room, the alien hisses at the sight of you. He jumps up towards the ventilation system, then stops. Spitting at you, he drops down from above, his hands start to reach out.";
                                  }
                              }
                              if (self.firstRanIntoAlien == false) {
                                  self.firstRanIntoAlien = true;
                                  "^Parting the thick smoke, you watch an alien slowly crawl out of the ventilation system - he spits at the sight of you. The creature jumps down to the deck, standing as tall as the room. You hear a hiss from deep inside the beast before he reaches out at you.";
                              } else {
                                  "^Parting the thick smoke, the alien hisses and spits. Angry that he found you in this room. Arching his back, the alien opens one of his mouths as he reaches out.";
                              }
                          }
                      }
                  } else {
                      self.alienEnterRoom = true;
                      ! ****************************************************
                      ! Move Alien To Destination & Print Whether It's Close
                      ! ****************************************************
                      if (self.alienMove) {
                          ! *******************************************
                          ! Alien Moves Randomly Based On ALIENMOVEMENT
                          ! *******************************************
                          mPos++;
                          if (mPos > 98) mPos = 0;
                          if (monster_move-->mPos > iAlienMovement) {
                              alienDistance = DistanceToAlien();
                              #Ifdef PRINTBACKEND;
                              print "^Distance To Alien:", alienDistance, ":", iOldAlienDistance, "^";
                              #EndIf;

                              self.alienIsMoving = true;
                              if (self.suppressAlienCloseBy == false) {
                                  if (alienDistance ~= 0) {
                                      self.printCloseBy = true;
                                      self.printFirstStop = true;
                                      if (alienDistance == 1) {
                                          if (self.printAlienClose) {
                                              self.printAlienClose = false;
                                              print "^Something is moving through these corridors, but it's close. Too close.^";
                                          } else {
                                              self.printAlienClose = true;
                                              print "^Whatever is making noise is close, and you're brave to be so near.^";
                                          }
                                      } else {
                                          ! ******************************
                                          ! Print Alien Is Close To Player
                                          ! ******************************
                                          ! *************************
                                          ! Alien Is Coming At Player
                                          ! *************************
                                          if (iOldAlienDistance > alienDistance) {
                                              switch (alienDistance) {
                                                  2: switch (DirectionAlienIsIn()) {
                                                         RETURN_FORWARD: DisplayAlienWarningComing(RETURN_FORWARD, RETURN_NEAR);
                                                         RETURN_AFT: DisplayAlienWarningComing(RETURN_AFT, RETURN_NEAR);
                                                         RETURN_PORT: DisplayAlienWarningComing(RETURN_PORT, RETURN_NEAR);
                                                         RETURN_STARBOARD: DisplayAlienWarningComing(RETURN_STARBOARD, RETURN_NEAR);
                                                         RETURN_ABOVE: DisplayAlienWarningComing(RETURN_ABOVE, RETURN_NEAR);
                                                         RETURN_BELOW: DisplayAlienWarningComing(RETURN_BELOW, RETURN_NEAR);
                                                     }
                                                  3: switch (DirectionAlienIsIn()) {
                                                         RETURN_FORWARD: DisplayAlienWarningComing(RETURN_FORWARD, RETURN_FAR);
                                                         RETURN_AFT: DisplayAlienWarningComing(RETURN_AFT, RETURN_FAR);
                                                         RETURN_PORT: DisplayAlienWarningComing(RETURN_PORT, RETURN_FAR);
                                                         RETURN_STARBOARD: DisplayAlienWarningComing(RETURN_STARBOARD, RETURN_FAR);
                                                         RETURN_ABOVE: DisplayAlienWarningComing(RETURN_ABOVE, RETURN_FAR);
                                                         RETURN_BELOW: DisplayAlienWarningComing(RETURN_BELOW, RETURN_FAR);
                                                     }
                                                  4: switch (DirectionAlienIsIn()) {
                                                         RETURN_FORWARD: DisplayAlienWarningComing(RETURN_FORWARD, RETURN_DISTANT);
                                                         RETURN_AFT: DisplayAlienWarningComing(RETURN_AFT, RETURN_DISTANT);
                                                         RETURN_PORT: DisplayAlienWarningComing(RETURN_PORT, RETURN_DISTANT);
                                                         RETURN_STARBOARD: DisplayAlienWarningComing(RETURN_STARBOARD, RETURN_DISTANT);
                                                         RETURN_ABOVE: DisplayAlienWarningComing(RETURN_ABOVE, RETURN_DISTANT);
                                                         RETURN_BELOW: DisplayAlienWarningComing(RETURN_BELOW, RETURN_DISTANT);
                                                     }
                                              }
                                          }
                                          ! **********************
                                          ! Alien Is Matching Pace
                                          ! **********************
                                          if (iOldAlienDistance == alienDistance) {
                                              switch (alienDistance) {
                                                  2: switch (DirectionAlienIsIn()) {
                                                         RETURN_FORWARD: DisplayAlienWarning(RETURN_FORWARD, RETURN_NEAR);
                                                         RETURN_AFT: DisplayAlienWarning(RETURN_AFT, RETURN_NEAR);
                                                         RETURN_PORT: DisplayAlienWarning(RETURN_PORT, RETURN_NEAR);
                                                         RETURN_STARBOARD: DisplayAlienWarning(RETURN_STARBOARD, RETURN_NEAR);
                                                         RETURN_ABOVE: DisplayAlienWarning(RETURN_ABOVE, RETURN_NEAR);
                                                         RETURN_BELOW: DisplayAlienWarning(RETURN_BELOW, RETURN_NEAR);
                                                     }
                                                  3: switch (DirectionAlienIsIn()) {
                                                         RETURN_FORWARD: DisplayAlienWarning(RETURN_FORWARD, RETURN_FAR);
                                                         RETURN_AFT: DisplayAlienWarning(RETURN_AFT, RETURN_FAR);
                                                         RETURN_PORT: DisplayAlienWarning(RETURN_PORT, RETURN_FAR);
                                                         RETURN_STARBOARD: DisplayAlienWarning(RETURN_STARBOARD, RETURN_FAR);
                                                         RETURN_ABOVE: DisplayAlienWarning(RETURN_ABOVE, RETURN_FAR);
                                                         RETURN_BELOW: DisplayAlienWarning(RETURN_BELOW, RETURN_FAR);
                                                     }
                                                  4: switch (DirectionAlienIsIn()) {
                                                         RETURN_FORWARD: DisplayAlienWarning(RETURN_FORWARD, RETURN_DISTANT);
                                                         RETURN_AFT: DisplayAlienWarning(RETURN_AFT, RETURN_DISTANT);
                                                         RETURN_PORT: DisplayAlienWarning(RETURN_PORT, RETURN_DISTANT);
                                                         RETURN_STARBOARD: DisplayAlienWarning(RETURN_STARBOARD, RETURN_DISTANT);
                                                         RETURN_ABOVE: DisplayAlienWarning(RETURN_ABOVE, RETURN_DISTANT);
                                                         RETURN_BELOW: DisplayAlienWarning(RETURN_BELOW, RETURN_DISTANT);
                                                     }
                                              }

                                          }
                                          ! *******************
                                          ! Alien Is Retreating
                                          ! *******************
                                          if (iOldAlienDistance < alienDistance) {
                                              switch (alienDistance) {
                                                  2: switch (DirectionAlienIsIn()) {
                                                         RETURN_FORWARD: DisplayAlienWarningGoing(RETURN_FORWARD, RETURN_NEAR);
                                                         RETURN_AFT: DisplayAlienWarningGoing(RETURN_AFT, RETURN_NEAR);
                                                         RETURN_PORT: DisplayAlienWarningGoing(RETURN_PORT, RETURN_NEAR);
                                                         RETURN_STARBOARD: DisplayAlienWarningGoing(RETURN_STARBOARD, RETURN_NEAR);
                                                         RETURN_ABOVE: DisplayAlienWarningGoing(RETURN_ABOVE, RETURN_NEAR);
                                                         RETURN_BELOW: DisplayAlienWarningGoing(RETURN_BELOW, RETURN_NEAR);
                                                     }
                                                  3: switch (DirectionAlienIsIn()) {
                                                         RETURN_FORWARD: DisplayAlienWarningGoing(RETURN_FORWARD, RETURN_FAR);
                                                         RETURN_AFT: DisplayAlienWarningGoing(RETURN_AFT, RETURN_FAR);
                                                         RETURN_PORT: DisplayAlienWarningGoing(RETURN_PORT, RETURN_FAR);
                                                         RETURN_STARBOARD: DisplayAlienWarningGoing(RETURN_STARBOARD, RETURN_FAR);
                                                         RETURN_ABOVE: DisplayAlienWarningGoing(RETURN_ABOVE, RETURN_FAR);
                                                         RETURN_BELOW: DisplayAlienWarningGoing(RETURN_BELOW, RETURN_FAR);
                                                     }
                                                  4: switch (DirectionAlienIsIn()) {
                                                         RETURN_FORWARD: DisplayAlienWarningGoing(RETURN_FORWARD, RETURN_DISTANT);
                                                         RETURN_AFT: DisplayAlienWarningGoing(RETURN_AFT, RETURN_DISTANT);
                                                         RETURN_PORT: DisplayAlienWarningGoing(RETURN_PORT, RETURN_DISTANT);
                                                         RETURN_STARBOARD: DisplayAlienWarningGoing(RETURN_STARBOARD, RETURN_DISTANT);
                                                         RETURN_ABOVE: DisplayAlienWarningGoing(RETURN_ABOVE, RETURN_DISTANT);
                                                         RETURN_BELOW: DisplayAlienWarningGoing(RETURN_BELOW, RETURN_DISTANT);
                                                     }
                                              }
                                          }
                                          ! Save Distance To Know If The Alien Is Getting Closer
                                          iOldAlienDistance = alienDistance;
                                      }
                                  } else {
                                      ! ********************************
                                      ! Reset Warnings Back To The Start
                                      ! ********************************
                                      self.printAlienClose = true;
                                      self.printCloseBy = false;
                                      iOldAlienDistance=5;
!                                      iAlienCloseBy=1;
                                  }
                              } else {
                                  self.suppressAlienCloseBy = false;
                              }
                          } else {
                              self.alienIsMoving = false;
                              #Ifdef PRINTBACKEND;
                              print "^The alien does not move.^";
                              #EndIf;
                              if (self.suppressAlienCloseBy == false) {
                                  if (DistanceToAlien() ~= 0) {
                                      if (self.printCloseBy) {
                                          if (self.printFirstStop) {
                                              self.printFirstStop = false;
                                              print "^Did it stop? You don't hear the noise, but you know it's still there.^";
                                          } else {
                                              if (DistanceToAlien() > 3) {
                                                  print "^You don't hear the noise anymore, but it's still lurking.^";
                                              } else {
                                                  print "^You don't hear the noise anymore, but you feel it's close.^";
                                              }
                                          }
                                      }
                                  }
                              } else {
                                  self.suppressAlienCloseBy = false;
                              }
                          }
                          IncreaseAlienSpeed();
                          if (self.alienIsMoving) {
                              iAlienMovement = iAlienSpeed;
                              switch (iMonsterDestination) {
                                  INFRMRY: AlienToInfirmary();
                                  HYPRSLPVLT: AlienToVault();
                                  PORTSHTTLBY: AlienToPortShuttle();
                                  STARBRDSHTTLBY: AlienToStarboardShuttle();
                                  SCIENCECRRDR: AlienToScienceCorridor();
                                  CAPTQRTRS: AlienToCaptainsQuarters();
                                  MAINTNNCGRGE: AlienToMaintenanceGarage();
                                  CONTROLRM: AlienToControlRoom();
                                  LOUNGE: AlienToLounge();
                                  FOODLCKER: AlienToFoodStorage();
                                  WEAPONSLCKER: AlienToWeaponsLocker();
                                  BRDG: AlienToBridge();
                                  FWDJUNDECKC: AlienToForwardStarboardJctnDeckC();
                                  FWDCOMPDECKC: AlienToForwardCompanionwayDeckC();
                                  AFTCOMPDECKC: AlienToAftCompanionwayDeckC();
                                  AFTJNCTNDECKA: AlienToAftJunctionDeckA();
                              }
                          }
                      }
                      ! **************************
                      ! Alien Hides For Five Turns
                      ! **************************
                      if (self.alienHide) {
                          iAlienHiding = iAlienHiding + 1;
                          ! ***********
                          ! Spawn Alien
                          ! ***********
                          if (iAlienHiding > 6) {
                              iAlienHiding = 0;
                              self.alienHide = false;
                              self.alienMove = true;
                              oldMonsterDes = iMonsterLoc;
                              iMonsterLoc++;
                              if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                              iMonsterDestination = monster_loc-->iMonsterLoc;
                              return AlienDestroysRoom(monster_loc-->oldMonsterDes);
                          } else {
                              #Ifdef PRINTBACKEND;
                              "^The alien hiding.";
                              #EndIf;
                          }
                      }
                  }
              } else {
                  self.advanceTime = true;
              }
          ],
          before [;
              Attack:
                  if (cattleProd in self) "If you hit yourself with the prod, you'd only end up pissing yourself.";
                  "Don't try to hurt yourself.";
              Rub, Touch:
                        "This might not be the right time to do that sort of thing.";
              Push, Pull, Turn, PushDir, Take:
                  "What are you even trying to do?";
              Go:
                  "You are already here.";
              Kiss:
                  "That's a little strange. Maybe you shouldn't.";
                    Talk:
                        "Do you usually go around talking to yourself?";
          ],
          life [;
                    Answer, Ask, AskTo, AskCreatureFor:
                        "Do you usually go around mumbling things?";
              Eat:
                  "Really?";
          ],
          isMoving false,
          alienHide false,
          alienMove false,
          inCorridor true,
          advanceTime true,
          advanceGravity true,
          mentionUndo true,
          printCloseBy false,
          firstItemTaken true,
          gravityWarning true,
          printFirstStop true,
          alienIsMoving false,
          alienEnterRoom false,
          gravityIncrease true,
          printAlienClose true,
          inComputerRoom false,
          firstRanIntoAlien false,
          firstGravityIncrease true,
          suppressAlienCloseBy false,
          firstWarningTriggered false,
          gravityVerbAlreadySeen false,
          xenomorphKnows false,
    has   animate concealed proper;

  [ PXF;
        if (player.xenomorphKnows) "But the xenomorph knows where you are.";
        player.xenomorphKnows = true;
        player.firstRanIntoAlien = true;
        "The xenomorph's faster than that.";
  ];

  [ DisplayAlienWarningComing direction distance;
        switch (direction) {
            RETURN_FORWARD:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering towards the front end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the front end of the ship. ";
            RETURN_AFT:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering towards the aft end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the aft end of the ship. ";
            RETURN_PORT:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering towards the port side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the port side of the ship. ";
            RETURN_STARBOARD:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering towards the starboard side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the starboard side of the ship. ";
            RETURN_ABOVE:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering above you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering above you. ";
            RETURN_BELOW:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering below you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering below you. ";
        }
        switch (distance) {
            RETURN_NEAR:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "It's near. Whatever it is, it's coming towards you.^";
                } else print "Near, and it's coming towards you.^";
            RETURN_FAR:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "It's a short distance away. It's coming towards you.^";
                } else print "A short distance away. It's coming towards you.^";
            RETURN_DISTANT:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "It's distant. Whatever it is, it's coming towards you.^";
                } else print "Distant, but it's coming towards you.^";
        }
  ];

  [ DisplayAlienWarning direction distance;
        switch (direction) {
            RETURN_FORWARD:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "^You hear something slithering towards the front end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the front end of the ship. ";
            RETURN_AFT:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "^You hear something slithering towards the aft end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the aft end of the ship. ";
            RETURN_PORT:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "^You hear something slithering towards the port side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the port side of the ship. ";
            RETURN_STARBOARD:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "^You hear something slithering towards the starboard side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the starboard side of the ship. ";
            RETURN_ABOVE:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "^You hear something slithering above you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering above you. ";
            RETURN_BELOW:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "^You hear something slithering below you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering below you. ";
        }
        switch (distance) {
            RETURN_NEAR: print "It's near.^";
            RETURN_FAR: print "It's a short distance away.^";
            RETURN_DISTANT: print "It's distant.^";
        }
  ];

  [ DisplayAlienWarningGoing direction distance;
        switch (direction) {
            RETURN_FORWARD:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering towards the front end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the front end of the ship. ";
            RETURN_AFT:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering towards the aft end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the aft end of the ship. ";
            RETURN_PORT:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering towards the port side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the port side of the ship. ";
            RETURN_STARBOARD:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering towards the starboard side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering towards the starboard side of the ship. ";
            RETURN_ABOVE:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering above you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering above you. ";
            RETURN_BELOW:
                if (player.firstWarningTriggered == false) {
                    print "^You hear something slithering below you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "^You hear something slithering below you. ";
        }
        switch (distance) {
            RETURN_NEAR:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "It's near. And it's retreating.^";
                } else print "Near, and it's retreating.^";
            RETURN_FAR:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "It's a short distance away. And it's retreating.^";
                } else print "A short distance away. And it's retreating.^";
            RETURN_DISTANT:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "It's distant. And it's retreating.^";
                } else print "Distant, and it's retreating.^";
        }
  ];

  [ DisplayListenAlienWarningComing direction distance;
        switch (direction) {
            RETURN_FORWARD:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering towards the front end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the front end of the ship. ";
            RETURN_AFT:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering towards the aft end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the aft end of the ship. ";
            RETURN_PORT:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering towards the port side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the port side of the ship. ";
            RETURN_STARBOARD:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering towards the starboard side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the starboard side of the ship. ";
            RETURN_ABOVE:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering above you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering above you. ";
            RETURN_BELOW:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering below you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering below you. ";
        }
        switch (distance) {
            RETURN_NEAR:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    "It's near. Whatever it is, it's coming towards you.";
                } else "Near, and it's coming towards you.";
            RETURN_FAR:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    "It's a short distance away. It's coming towards you.";
                } else "A short distance away. It's coming towards you.";
            RETURN_DISTANT:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    "It's distant. Whatever it is, it's coming towards you.";
                } else "Distant, but it's coming towards you.";
        }
  ];

  [ DisplayListenAlienWarning direction distance;
        switch (direction) {
            RETURN_FORWARD:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "You hear something slithering towards the front end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the front end of the ship. ";
            RETURN_AFT:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "You hear something slithering towards the aft end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the aft end of the ship. ";
            RETURN_PORT:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "You hear something slithering towards the port side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the port side of the ship. ";
            RETURN_STARBOARD:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "You hear something slithering towards the starboard side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the starboard side of the ship. ";
            RETURN_ABOVE:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "You hear something slithering above you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering above you. ";
            RETURN_BELOW:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    print "You hear something slithering below you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering below you. ";
        }
        switch (distance) {
            RETURN_NEAR: "It's near.";
            RETURN_FAR: "It's a short distance away.";
            RETURN_DISTANT: "It's distant.";
        }
  ];

  [ DisplayListenAlienWarningGoing direction distance;
        switch (direction) {
            RETURN_FORWARD:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering towards the front end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the front end of the ship. ";
            RETURN_AFT:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering towards the aft end of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the aft end of the ship. ";
            RETURN_PORT:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering towards the port side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the port side of the ship. ";
            RETURN_STARBOARD:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering towards the starboard side of the ship, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering towards the starboard side of the ship. ";
            RETURN_ABOVE:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering above you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering above you. ";
            RETURN_BELOW:
                if (player.firstWarningTriggered == false) {
                    print "You hear something slithering below you, like an enormous snake looking for its next meal. But then, scratching with claws? This can't be good.^^";
                } else print "You hear something slithering below you. ";
        }
        switch (distance) {
            RETURN_NEAR:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    "It's near. And it's retreating.";
                } else "Near, and it's retreating.";
            RETURN_FAR:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    "It's a short distance away. And it's retreating.";
                } else "A short distance away. And it's retreating.";
            RETURN_DISTANT:
                if (player.firstWarningTriggered == false) {
                    player.firstWarningTriggered = true;
                    "It's distant. And it's retreating.";
                } else "Distant, and it's retreating.";
        }
  ];

  [ PlayerOnADeck;
        if (player in bridge) rtrue;
        if (player in computerRoom) rtrue;
        if (player in galley) rtrue;
        if (player in captainsQuarters) rtrue;
        if (player in infirmary) rtrue;
        if (player in forwardCompanionwayDeckA) rtrue;
        if (player in hypersleepVault) rtrue;
        if (player in maintenanceLiftDeckA) rtrue;
        if (player in aftJunctionDeckA) rtrue;
        if (player in personalLockerRoom) rtrue;
        rfalse;
  ];

  [ PlayerOnBDeck;
        if (player in maintenanceLiftDeckB) rtrue;
        if (player in forwardPortJunctionDeckB) rtrue;
        if (player in forwardStarboardJunctionDeckB) rtrue;
        if (player in crewLounge) rtrue;
        if (player in weaponsLocker) rtrue;
        if (player in passagewayDeckB) rtrue;
        if (player in aftCompanionwayDeckB) rtrue;
        if (player in foodLockerCorridorDeckB) rtrue;
        if (player in foodStorage) rtrue;
        if (player in portShuttleBay) rtrue;
        if (player in aftJunctionDeckB) rtrue;
        if (player in starboardShuttleBay) rtrue;
        rfalse;
  ];

  [ PlayerOnCDeck;
        if (player in forwardCompanionwayDeckC) rtrue;
        if (player in forwardStarboardJunctionDeckC) rtrue;
        if (player in maintenanceGarage) rtrue;
        if (player in clawChamber) rtrue;
        if (player in aftPortJunctionDeckC) rtrue;
        if (player in aftCompanionwayDeckC) rtrue;
        if (player in aftStarboardJunctionDeckC) rtrue;
        if (player in controlRoomDeckC) rtrue;
        rfalse;
  ];

  [ PlayerInCorridorBDeck;
        if (player in forwardPortJunctionDeckB) rtrue;
        if (player in forwardStarboardJunctionDeckB) rtrue;
        if (player in passagewayDeckB) rtrue;
        if (player in foodLockerCorridorDeckB) rtrue;
        if (player in aftJunctionDeckB) rtrue;
        if (player in starboardJunctionDeckB) rtrue;
        if (player in forwardCorridorDeckB) rtrue;
        if (player in scienceCorridorDeckB) rtrue;
        rfalse;
  ];

  [ PlayerInCorridorCDeck;
        if (player in forwardStarboardJunctionDeckC) rtrue;
        if (player in aftPortJunctionDeckC) rtrue;
        if (player in aftStarboardJunctionDeckC) rtrue;
        rfalse;
  ];

  [ PlayerOnForeBDeck;
        if (player in instrumentationBay) rtrue;
        if (player in scienceCorridorDeckB) rtrue;
        if (player in forwardCorridorDeckB) rtrue;
        if (player in forwardCompanionwayDeckB) rtrue;
        if (player in starboardJunctionDeckB) rtrue;
        rfalse;
  ];
