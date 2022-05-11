
! ---------------------------------------------------------------------------- !
!       ALIEN. 10/30/21
!
!

  Object  alien "alien"
    with  name 'alien' 'xenomorph' 'thing' 'creature' 'monster' 'beast' 'it',
          describe [;
              rtrue;
          ],
          daemon [;
              deadflag = 1;
              "^The alien jumps before you can get away, throwing you to the ground and breaking bones. With the creature on top of you, his large hand comes crashing down. Talons tear into your flesh. When the beast is done, it doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
          ],
          before [;
              Attack:
                  self.hitFirstTime = true;
                  player.firstItemTaken = false;
                  player.firstRanIntoAlien = true;
                  cattleProd.firstTime = false;
                  if (second == sledgehammer) {
                      if (sledgehammer in vortexBag) {
                          print "The sledgehammer is in the vortex bag and would take too long to pull out.^^";
                          deadflag = 1;
                          "You swing helplessly at the alien, arms flailing like an angry schoolgirl. The creature reacts by plunging his talons deep into your flesh. When the beast is done, it doesn't take long before you bleed out and the ship's crushed from the sun's pressure.";
                      } else {
                          <<Swing sledgehammer>>;
                      }
                  }
                  if (second == crowbar) {
                      <<Swing crowbar>>;
                  }
                  if (second == stunBaton) {
                      <<Swing stunBaton>>;
                  }
                  if (sledgehammer in player) {
                      if (second == cattleProd && sledgehammer.alreadyAttacked == false) print "The cattle prod is in the vortex bag and would take too long to pull out.^^";
                      <<Swing sledgehammer second>>;
                  }
                  if (cattleProd in player || second == cattleProd) {
                      if (cattleProd in vortexBag) {
                          move cattleProd to player;
                          print "(first taking the cattle prod)^";
                      }
                      if (iCattleProdCharge == 0) {
                          deadflag = 1;
                          "You try to stick the alien with the cattle prod, but nothing happens. You realize all too late that the rod is out of power. When the alien's done, you bleed out before the ship's crushed from the sun's pressure.";
                      }
                      if (stunBaton in player) move stunBaton to vortexBag;
                      iCattleProdCharge--;
                      StopDaemon(self);
                      remove self;
                      player.alienHide = true;
                      player.alienMove = false;
                      if (iCattleProdCharge == 2) "Standing in front of the beast, just about to crap yourself, you swing the cattle prod blindly at the alien, lucky to connect with its skin. Electricity pops, and then you smell burning flesh - the beast hisses and spits. It thinks for a second but then jumps into the closest vent, leaving you behind.";
                      if (iCattleProdCharge == 1) "The creature cries out in pain as you plunge the cattle prod deep into the middle of his torso. He turns like he'll attack, then cries out one more time before jumping up into the ventilation system.";
                      "You hit the creature as hard as you can with the rod, but he just shakes his head. Screaming, he spits. Then jumps into the ventilation system.^^You look down at the handle. You're out of juice.";
                  }
                  if (stunBaton in player) {
                      <<Swing stunBaton>>;
                  }
                  deadflag = 1;
                  "You swing helplessly at the alien, arms flailing like an angry schoolgirl. The creature reacts by plunging his talons deep into your flesh. When the beast is done, it doesn't take long before you bleed out and the ship's crushed from the sun's pressure.";
              Examine:
                  deadflag = 1;
                  "The alien glistens with a metallic shine. His large, bulbous head arched back. There's a long row of sharp teeth that run up the side of his mouth, almost like he's smiling. Eyes burn deep into you. Arm's outstretched and tense.^^Then his mouth opens, the creature lunges, and the jaws come for you. When the beast is done, it doesn't take long before you bleed out and the ship's crushed from the pressure of the sun.";
              default:
                  deadflag = 1;
                  "Before you can do anything to the creature, the alien arches his bulbous head back. Eyes burning deep into you. Then his mouth opens, the creature lunges, and the jaws come for you. When the beast's done, it doesn't take long before you bleed out and the ship's crushed from the sun's pressure.";
          ],
          life [;
              default:
                  deadflag = 1;
                  "Before you can do anything to the creature, the alien arches his bulbous head back. Eyes burning deep into you. Then his mouth opens, the creature lunges, and the jaws come for you. When the creature's done, it doesn't take long before you bleed out and the ship's crushed from the sun's pressure.";
          ],
          orders [;
              default:
                  deadflag = 1;
                  "The alien isn't going to listen to you. He arches his bulbous head back. Eyes burning deep into you. Then his mouth opens, the creature lunges, and the jaws come for you. When the creature's done, it doesn't take long before you bleed out and the ship's crushed from the sun's pressure.";
          ],
          sleeping true,
          waitOneTurn false,
          hitFirstTime false,
          creatureMoving false,
          destroysFirstRoom true,
    has   animate male concealed;

  [ AlienDestroysFirstRoom monsterLoc;
      alien.destroysFirstRoom = true;
      switch (monsterLoc) {
          INFRMRY:
              move alien to infirmary;
              if (player in infirmary) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (knitter in infirmary) knitter.spitOn = true;
              if (medkit in infirmaryCabinet) {
                  medkit.spitOn = true;
                  move medkit to infirmary;
              }
              #EndIf;
              move infirmaryAcid to infirmary;
              give infirmaryCabinet ~container;
              give infirmaryTable ~supporter;
              infirmary.alienWrecked = true;
              return IsInfirmaryDestroyed();

          HYPRSLPVLT:
              move alien to hypersleepVault;
              if (player in hypersleepVault) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (necklace in hypersleepVault) necklace.spitOn = true;
              #EndIf;
              move hypersleepVaultAcid to hypersleepVault;
              remove hypersleepVaultSolution;
              hypersleepVault.alienWrecked = true;
              return IsVaultDestroyed();

          PORTSHTTLBY:
              move alien to portShuttleBay;
              if (player in portShuttleBay) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (extinguisher in portShuttleBay) extinguisher.spitOn = true;
              #EndIf;
              move portShuttleBayAcid to portShuttleBay;
              portShuttleBay.alienWrecked = true;
              return IsPortShuttleBayDestroyed();

          STARBRDSHTTLBY:
              move alien to starboardShuttleBay;
              if (player in starboardShuttleBay) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (spacesuit in starboardShuttleBay) {
                  spacesuit.spitOn = true;
              }
              #EndIf;
              move starboardShuttleBayAcid to starboardShuttleBay;
              starboardShuttleBay.alienWrecked = true;
              return IsStarboardShuttleBayDestroyed();

          SCIENCECRRDR:
              move alien to scienceCorridorDeckB;
              if (player in scienceCorridorDeckB) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              return IsScienceCorridorDestroyed();

          CAPTQRTRS:
              move alien to captainsQuarters;
              if (player in captainsQuarters) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (kabar in captainsQuarters) kabar.spitOn = true;
              #EndIf;
              ! ***********************************
              ! Player Never Took The Red Flashcard
              ! ***********************************
              if (captainsQuarters.takenRedCard == false) move redFlashcard to captainsQuarters;
              give captainsQuartersDesk ~supporter;
              move captainsQuartersAcid to captainsQuarters;
              move captainsQuartersWood to captainsQuarters;
              captainsQuarters.alienWrecked = true;
              return IsCaptainsQuartersDestroyed();

          MAINTNNCGRGE:
              move alien to maintenanceGarage;
              if (player in maintenanceGarage) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;

              #EndIf;
              ! **************************************
              ! Player Never Took The Yellow Flashcard
              ! **************************************
              if (yellowFlashcard.takenYellowcard == false) {
                  move yellowFlashcard to maintenanceGarage;
                  move maintenanceGarageBench to maintenanceGarage;
              }
              give maintenanceGarageBench ~supporter;
              move maintenanceGarageAcid to maintenanceGarage;
              maintenanceGarage.alienWrecked = true;
              return IsMaintenanceGarageDestroyed();

          LOUNGE:
              move alien to crewLounge;
              if (player in crewLounge) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (crewLounge.takenMusicBox == false) musicBox.spitOn = true;
              #EndIf;
              move crewLoungeAcid to crewLounge;
              crewLounge.alienWrecked = true;
              return IsLoungeDestroyed();

          default:
              move alien to controlRoomDeckC;
              if (player in controlRoomDeckC) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              if (laptop in controlRoomDeckCBench) {
                  #Ifdef DESTROYOBJECTS;
                  laptop.spitOn = true;
                  laptop.&name-->3 = 'sludge';
                  laptop.&name-->4 = 'broken';
                  laptop.&name-->5 = 'electronics';
                  laptop.&name-->6 = 'internal';
                  laptop.&name-->7 = 'circuitry';
                  #EndIf;
              }
              if (controlRoomDeckCCabinet.openedFirstTime == false) {
                  controlRoomDeckCCabinet.openedFirstTime = true;
                  move crowbar to controlRoomDeckC;
                  move controlRoomDeckCCabinet to controlRoomDeckC;
              }
              move controlRoomDeckCAcid to controlRoomDeckC;
              controlRoomDeckC.closetOpen = true;
              controlRoomDeckC.alienWrecked = true;
              controlRoomDeckCCabinet.alienWrecked = true;
              return IsControlRoomDestroyed();
      }
  ];

  [ AlienDestroysRoom monsterLoc;
      alien.destroysFirstRoom = false;
      switch (monsterLoc) {
          INFRMRY:
              move alien to infirmary;
              if (player in infirmary) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (knitter in infirmary) knitter.spitOn = true;
              if (medkit in infirmaryCabinet) {
                  medkit.spitOn = true;
                  move medkit to infirmary;
              }
              #EndIf;
              move infirmaryAcid to infirmary;
              give infirmaryCabinet ~container;
              give infirmaryTable ~supporter;
              infirmary.alienWrecked = true;
              return IsInfirmaryDestroyed();

          HYPRSLPVLT:
              move alien to hypersleepVault;
              if (player in hypersleepVault) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (necklace in hypersleepVault) necklace.spitOn = true;
              #EndIf;
              move hypersleepVaultAcid to hypersleepVault;
              remove hypersleepVaultSolution;
              hypersleepVault.alienWrecked = true;
              return IsVaultDestroyed();

          PORTSHTTLBY:
              move alien to portShuttleBay;
              if (player in portShuttleBay) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (extinguisher in portShuttleBay) extinguisher.spitOn = true;
              #EndIf;
              move portShuttleBayAcid to portShuttleBay;
              portShuttleBay.alienWrecked = true;
              return IsPortShuttleBayDestroyed();

          STARBRDSHTTLBY:
              move alien to starboardShuttleBay;
              if (player in starboardShuttleBay) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (spacesuit in starboardShuttleBay) {
                  spacesuit.spitOn = true;
              }
              #EndIf;
              move starboardShuttleBayAcid to starboardShuttleBay;
              starboardShuttleBay.alienWrecked = true;
              return IsStarboardShuttleBayDestroyed();

          SCIENCECRRDR:
              move alien to scienceCorridorDeckB;
              if (player in scienceCorridorDeckB) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              return IsScienceCorridorDestroyed();

          CAPTQRTRS:
              move alien to captainsQuarters;
              if (player in captainsQuarters) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (kabar in captainsQuarters) kabar.spitOn = true;
              #EndIf;
              ! ***********************************
              ! Player Never Took The Red Flashcard
              ! ***********************************
              if (captainsQuarters.takenRedCard == false) move redFlashcard to captainsQuarters;
              give captainsQuartersDesk ~supporter;
              move captainsQuartersAcid to captainsQuarters;
              move captainsQuartersWood to captainsQuarters;
              captainsQuarters.alienWrecked = true;
              return IsCaptainsQuartersDestroyed();

          MAINTNNCGRGE:
              move alien to maintenanceGarage;
              if (player in maintenanceGarage) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;

              #EndIf;
              ! **************************************
              ! Player Never Took The Yellow Flashcard
              ! **************************************
              if (yellowFlashcard.takenYellowcard == false) {
                  move yellowFlashcard to maintenanceGarage;
                  move maintenanceGarageBench to maintenanceGarage;
              }
              give maintenanceGarageBench ~supporter;
              move maintenanceGarageAcid to maintenanceGarage;
              maintenanceGarage.alienWrecked = true;
              return IsMaintenanceGarageDestroyed();

          LOUNGE:
              move alien to crewLounge;
              if (player in crewLounge) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (crewLounge.takenMusicBox == false) musicBox.spitOn = true;
              #EndIf;
              move crewLoungeAcid to crewLounge;
              crewLounge.alienWrecked = true;
              return IsLoungeDestroyed();

          WEAPONSLCKER:
              move alien to weaponsLocker;
              if (player in weaponsLocker) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (weaponsLocker.takenBaton == false) stunBaton.spitOn = true;
              if (weaponsLocker.takenArmor == false) trooperArmor.spitOn = true;
              #EndIf;
              passagewayDeckBDoor.&name-->8 = 'broken';
              passagewayDeckBDoor.&name-->9 = 'torn';
              weaponsLockerHatch.&name-->3 = 'broken';
              move weaponsLockerAcid to weaponsLocker;
              weaponsLocker.alienWrecked = true;
              return IsWeapLockDestroyed();

          FOODLCKER:
              move alien to foodStorage;
              if (player in foodStorage) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              #Ifdef DESTROYOBJECTS;
              if (foodStorage.takenWine == false) wine.spitOn = true;
              #EndIf;
              foodStorageDoor.&name-->5 = 'broken';
              foodStorageDoor.&name-->6 = 'dented';
              foodStorageDoor.&name-->7 = 'gaping';
              foodStorageDoor.&name-->8 = 'hole';
              foodLockerCorridorDeckBDoor.&name-->6 = 'broken';
              foodLockerCorridorDeckBDoor.&name-->7 = 'torn';
              move foodStorageAcid to foodStorage;
              foodStorage.alienWrecked = true;
              return IsFoodLockDestroyed();

          default:
              move alien to controlRoomDeckC;
              if (player in controlRoomDeckC) {
                  StartDaemon(alien);
                  "^The alien crawls out of the ventilation system and hisses at the sight of you. Then, dropping down from above, his hands reach out.";
              }
              if (laptop in controlRoomDeckCBench) {
                  #Ifdef DESTROYOBJECTS;
                  laptop.spitOn = true;
                  laptop.&name-->3 = 'sludge';
                  laptop.&name-->4 = 'broken';
                  laptop.&name-->5 = 'electronics';
                  laptop.&name-->6 = 'internal';
                  laptop.&name-->7 = 'circuitry';
                  #EndIf;
              }
              if (controlRoomDeckCCabinet.openedFirstTime == false) {
                  controlRoomDeckCCabinet.openedFirstTime = true;
                  move crowbar to controlRoomDeckC;
                  move controlRoomDeckCCabinet to controlRoomDeckC;
              }
              move controlRoomDeckCAcid to controlRoomDeckC;
              controlRoomDeckC.closetOpen = true;
              controlRoomDeckC.alienWrecked = true;
              controlRoomDeckCCabinet.alienWrecked = true;
              return IsControlRoomDestroyed();
      }
  ];

  ! **********************************************************
  ! Used if the Alien wakes after the pipe on C deck is broken
  ! **********************************************************
  [ AlienWakes monsterLoc;
        alien.destroysFirstRoom = true;
        switch (monsterLoc) {
            INFRMRY:
                move alien to infirmary;
                #Ifdef DESTROYOBJECTS;
                if (knitter in infirmary) knitter.spitOn = true;
                if (medkit in infirmaryCabinet) {
                    medkit.spitOn = true;
                    move medkit to infirmary;
                }
                #EndIf;
                move infirmaryAcid to infirmary;
                give infirmaryCabinet ~container;
                give infirmaryTable ~supporter;
                infirmary.alienWrecked = true;
                infirmary.destroyedYet = true;
                player.firstItemTaken = false;
                "From somewhere above you, you hear the sound of wood and plastic crashing into one another. Then a
                pause, only to hear wood break and pop-off in succession. After the last beam is snapped, a
                high-pitched cry rings out. You have a feeling you're not alone.";

            HYPRSLPVLT:
                move alien to hypersleepVault;
                #Ifdef DESTROYOBJECTS;
                if (necklace in hypersleepVault) necklace.spitOn = true;
                #EndIf;
                move hypersleepVaultAcid to hypersleepVault;
                remove hypersleepVaultSolution;
                hypersleepVault.alienWrecked = true;
                hypersleepVault.destroyedYet = true;
                player.firstItemTaken = false;
                "From somewhere above you, a shattering crash rings throughout the ship. It's followed by
                the sound of containers being thrown around one of the rooms. When the thudding stops, a
                high-pitched cry follows. You have a feeling you're not alone.";

            PORTSHTTLBY:
                move alien to portShuttleBay;
                #Ifdef DESTROYOBJECTS;
                if (extinguisher in portShuttleBay) extinguisher.spitOn = true;
                #EndIf;
                move portShuttleBayAcid to portShuttleBay;
                portShuttleBay.alienWrecked = true;
                portShuttleBay.destroyedYet = true;
                player.firstItemTaken = false;
                "Above you, in the aft portion of the ship, you hear the sound of scratching knives that grate
                on your nerves. It rings out in a thrashing of metal that fails to break. When it comes to
                an end, you ignore the chill in your bones. You have a feeling you're not alone.";

            STARBRDSHTTLBY:
                move alien to starboardShuttleBay;
                #Ifdef DESTROYOBJECTS;
                if (spacesuit in starboardShuttleBay) {
                    spacesuit.spitOn = true;
                }
                #EndIf;
                move starboardShuttleBayAcid to starboardShuttleBay;
                starboardShuttleBay.alienWrecked = true;
                starboardShuttleBay.destroyedYet = true;
                player.firstItemTaken = false;
                "Above you, in the aft portion of the ship, you hear the sound of plastic being torn apart.
                The sound of synthetics being shredded. You have a feeling you're not alone.";

            SCIENCECRRDR:
                move alien to scienceCorridorDeckB;
                scienceCorridorDeckB.destroyedYet = true;
                player.firstItemTaken = false;
                "From somewhere above you, you hear a high-pitched scream and then smashing and banging.
                The sounds echo through the empty derelict. You have a feeling you're not alone.";

            CAPTQRTRS:
                move alien to captainsQuarters;
                #Ifdef DESTROYOBJECTS;
                if (kabar in captainsQuarters) kabar.spitOn = true;
                #EndIf;
                ! ***********************************
                ! Player Never Took The Red Flashcard
                ! ***********************************
                if (captainsQuarters.takenRedCard == false) move redFlashcard to captainsQuarters;
                give captainsQuartersDesk ~supporter;
                move captainsQuartersAcid to captainsQuarters;
                move captainsQuartersWood to captainsQuarters;
                captainsQuarters.alienWrecked = true;
                captainsQuarters.destroyedYet = true;
                player.firstItemTaken = false;
                "From somewhere above you, towards the forward end of the ship, you hear the sound of wood
                being crushed in another room. Like it snapped in half. Then metal being thrown around? It's
                hard to tell. You have a feeling you're not alone.";

            MAINTNNCGRGE:
                move alien to maintenanceGarage;
                #Ifdef DESTROYOBJECTS;

                #EndIf;
                ! **************************************
                ! Player Never Took The Yellow Flashcard
                ! **************************************
                if (yellowFlashcard.takenYellowcard == false) {
                    move yellowFlashcard to maintenanceGarage;
                    move maintenanceGarageBench to maintenanceGarage;
                }
                give maintenanceGarageBench ~supporter;
                move maintenanceGarageAcid to maintenanceGarage;
                maintenanceGarage.alienWrecked = true;
                maintenanceGarage.destroyedYet = true;
                player.firstItemTaken = false;
                if (player in forwardCompanionwayDeckC) {
                    print "From the room next to you";
                } else {
                    print "From somewhere on this deck";
                }
                ", the sound of metal cracking in half echoes through the vessel with a force
                so strong you think you feel it before you hear it. The massive blast
                rings through the vessel, giving you pause. You have a feeling you're not alone.";

            LOUNGE:
                move alien to crewLounge;
                #Ifdef DESTROYOBJECTS;
                if (crewLounge.takenMusicBox == false) musicBox.spitOn = true;
                #EndIf;
                move crewLoungeAcid to crewLounge;
                crewLounge.alienWrecked = true;
                crewLounge.destroyedYet = true;
                player.firstItemTaken = false;
                "From somewhere above you, towards the starboard side of the ship, the sound
                of tearing and scratching, along with a high-pitched scream, reaches your ears.
                You cringe for a second as the spaceship rings hollow. You have a feeling you're not alone.";

            default:
                move alien to controlRoomDeckC;
                if (laptop in controlRoomDeckCBench) {
                    #Ifdef DESTROYOBJECTS;
                    laptop.spitOn = true;
                    laptop.&name-->3 = 'sludge';
                    laptop.&name-->4 = 'broken';
                    laptop.&name-->5 = 'electronics';
                    laptop.&name-->6 = 'internal';
                    laptop.&name-->7 = 'circuitry';
                    #EndIf;
                }
                if (controlRoomDeckCCabinet.openedFirstTime == false) {
                    controlRoomDeckCCabinet.openedFirstTime = true;
                    move crowbar to controlRoomDeckC;
                    move controlRoomDeckCCabinet to controlRoomDeckC;
                }
                move controlRoomDeckCAcid to controlRoomDeckC;
                controlRoomDeckC.closetOpen = true;
                controlRoomDeckC.alienWrecked = true;
                controlRoomDeckCCabinet.alienWrecked = true;
                controlRoomDeckC.destroyedYet = true;
                player.firstItemTaken = false;
                "From somewhere on this deck, rings out the sound of cans being tossed around.
                Then metal as it's bounced off the walls in one of the rooms. It ends with a
                bit of scraping and scratching. You have a feeling you're not alone.";
        }
    ];

  [ AlienToInfirmary;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the infirmary.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftCompanionwayDeckC;
            aftCompanionwayDeckC:
                move alien to aftStarboardJunctionDeckC;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to forwardStarboardJunctionDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to infirmary;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckA;
            forwardCompanionwayDeckC:
                move alien to forwardCompanionwayDeckB;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to forwardCompanionwayDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                iMonsterLoc++;
                if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef DESTROYOBJECTS;
                if (knitter in infirmary) knitter.spitOn = true;
                if (medkit in infirmaryCabinet) {
                    medkit.spitOn = true;
                    move medkit to infirmary;
                }
                #EndIf;
                move infirmaryAcid to infirmary;
                give infirmaryCabinet ~container;
                give infirmaryTable ~supporter;
                infirmary.alienWrecked = true;
                return IsInfirmaryDestroyed();
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToVault;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the hypersleep vault.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftCompanionwayDeckC;
            aftCompanionwayDeckC:
                move alien to aftStarboardJunctionDeckC;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to forwardStarboardJunctionDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to hypersleepVault;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckA;
            forwardCompanionwayDeckC:
                move alien to forwardCompanionwayDeckB;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to forwardCompanionwayDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                iMonsterLoc++;
                if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef DESTROYOBJECTS;
                if (necklace in hypersleepVault) necklace.spitOn = true;
                #EndIf;
                move hypersleepVaultAcid to hypersleepVault;
                remove hypersleepVaultSolution;
                hypersleepVault.alienWrecked = true;
                return IsVaultDestroyed();
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to forwardCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToPortShuttle;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the port shuttle bay.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftJunctionDeckB;
            aftCompanionwayDeckC:
                move alien to aftCompanionwayDeckB;
            aftJunctionDeckB:
                move alien to portShuttleBay;
            aftStarboardJunctionDeckC:
                move alien to aftCompanionwayDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to forwardCompanionwayDeckB;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckC;
            forwardCompanionwayDeckC:
                move alien to forwardStarboardJunctionDeckC;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to aftStarboardJunctionDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                iMonsterLoc++;
                if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef DESTROYOBJECTS;
                if (extinguisher in portShuttleBay) extinguisher.spitOn = true;
                #EndIf;
                move portShuttleBayAcid to portShuttleBay;
                portShuttleBay.alienWrecked = true;
                return IsPortShuttleBayDestroyed();
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToStarboardShuttle;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the starboard shuttle bay.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftJunctionDeckB;
            aftCompanionwayDeckC:
                move alien to aftCompanionwayDeckB;
            aftJunctionDeckB:
                move alien to starboardShuttleBay;
            aftStarboardJunctionDeckC:
                move alien to aftCompanionwayDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to forwardCompanionwayDeckB;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckC;
            forwardCompanionwayDeckC:
                move alien to forwardStarboardJunctionDeckC;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to aftStarboardJunctionDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                iMonsterLoc++;
                if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef DESTROYOBJECTS;
                if (spacesuit in starboardShuttleBay) {
                    spacesuit.spitOn = true;
                }
                #EndIf;
                move starboardShuttleBayAcid to starboardShuttleBay;
                starboardShuttleBay.alienWrecked = true;
                return IsStarboardShuttleBayDestroyed();
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToScienceCorridor;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the science corridor.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftCompanionwayDeckC;
            aftCompanionwayDeckC:
                move alien to aftStarboardJunctionDeckC;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to forwardStarboardJunctionDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to forwardCompanionwayDeckB;
            forwardCompanionwayDeckB:
                move alien to scienceCorridorDeckB;
            forwardCompanionwayDeckC:
                move alien to forwardCompanionwayDeckB;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to forwardCompanionwayDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                iMonsterLoc++;
                if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef PRINTBACKEND;
                    "^The alien arrives at the science corridor and looks around.";
                #EndIf;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToCaptainsQuarters;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the captain's quarters.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftCompanionwayDeckC;
            aftCompanionwayDeckC:
                move alien to aftStarboardJunctionDeckC;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to forwardStarboardJunctionDeckC;
            captainsQuarters:
                iMonsterLoc++;
                if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef DESTROYOBJECTS;
                if (kabar in captainsQuarters) kabar.spitOn = true;
                #EndIf;
                if (captainsQuarters.takenRedCard == false) move redFlashcard to captainsQuarters;
                give captainsQuartersDesk ~supporter;
                move captainsQuartersAcid to captainsQuarters;
                move captainsQuartersWood to captainsQuarters;
                captainsQuarters.alienWrecked = true;
                return IsCaptainsQuartersDestroyed();
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to galley;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckA;
            forwardCompanionwayDeckC:
                move alien to forwardCompanionwayDeckB;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to forwardCompanionwayDeckC;
            galley:
                move alien to captainsQuarters;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToMaintenanceGarage;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the maintenance garage.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftCompanionwayDeckC;
            aftCompanionwayDeckC:
                move alien to aftStarboardJunctionDeckC;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to forwardStarboardJunctionDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to forwardCompanionwayDeckB;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckC;
            forwardCompanionwayDeckC:
                move alien to maintenanceGarage;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to forwardCompanionwayDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                iMonsterLoc++;
                if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                if (yellowFlashcard.takenYellowcard == false) {
                    move yellowFlashcard to maintenanceGarage;
                    move maintenanceGarageBench to maintenanceGarage;
                }
                give maintenanceGarageBench ~supporter;
                move maintenanceGarageAcid to maintenanceGarage;
                maintenanceGarage.alienWrecked = true;
                return IsMaintenanceGarageDestroyed();
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToControlRoom;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the control room.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftCompanionwayDeckC;
            aftCompanionwayDeckC:
                move alien to controlRoomDeckC;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to aftCompanionwayDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                iMonsterLoc++;
                if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                if (laptop in controlRoomDeckCBench) {
                    #Ifdef DESTROYOBJECTS;
                    laptop.spitOn = true;
                    laptop.&name-->3 = 'sludge';
                    laptop.&name-->4 = 'broken';
                    laptop.&name-->5 = 'electronics';
                    laptop.&name-->6 = 'internal';
                    laptop.&name-->7 = 'circuitry';
                    #EndIf;
                }
                if (controlRoomDeckCCabinet.openedFirstTime == false) {
                    controlRoomDeckCCabinet.openedFirstTime = true;
                    move crowbar to controlRoomDeckC;
                    move controlRoomDeckCCabinet to controlRoomDeckC;
                }
                move controlRoomDeckCAcid to controlRoomDeckC;
                controlRoomDeckC.closetOpen = true;
                controlRoomDeckC.alienWrecked = true;
                controlRoomDeckCCabinet.alienWrecked = true;
                return IsControlRoomDestroyed();
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to forwardCompanionwayDeckB;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckC;
            forwardCompanionwayDeckC:
                move alien to forwardStarboardJunctionDeckC;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to aftStarboardJunctionDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToLounge;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the crew lounge.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to foodLockerCorridorDeckB;
            aftCompanionwayDeckC:
                move alien to aftCompanionwayDeckB;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to aftCompanionwayDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                iMonsterLoc++;
                if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef DESTROYOBJECTS;
                if (crewLounge.takenMusicBox == false) musicBox.spitOn = true;
                #EndIf;
                move crewLoungeAcid to crewLounge;
                crewLounge.alienWrecked = true;
                return IsLoungeDestroyed();
            foodLockerCorridorDeckB:
                move alien to forwardStarboardJunctionDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to forwardCompanionwayDeckB;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckC;
            forwardCompanionwayDeckC:
                move alien to forwardStarboardJunctionDeckC;
            forwardStarboardJunctionDeckB:
                move alien to crewLounge;
            forwardStarboardJunctionDeckC:
                move alien to aftStarboardJunctionDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToFoodStorage;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards food storage.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to foodLockerCorridorDeckB;
            aftCompanionwayDeckC:
                move alien to aftCompanionwayDeckB;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to aftCompanionwayDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to foodStorage;
            foodStorage:
                iMonsterLoc++;
                if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef DESTROYOBJECTS;
                if (foodStorage.takenWine == false) wine.spitOn = true;
                #EndIf;
                foodStorageDoor.&name-->5 = 'broken';
                foodStorageDoor.&name-->6 = 'dented';
                foodStorageDoor.&name-->7 = 'gaping';
                foodStorageDoor.&name-->8 = 'hole';
                foodLockerCorridorDeckBDoor.&name-->6 = 'broken';
                foodLockerCorridorDeckBDoor.&name-->7 = 'torn';
                move foodStorageAcid to foodStorage;
                foodStorage.alienWrecked = true;
                return IsFoodLockDestroyed();
            forwardCompanionwayDeckA:
                move alien to forwardCompanionwayDeckB;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckC;
            forwardCompanionwayDeckC:
                move alien to forwardStarboardJunctionDeckC;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to aftStarboardJunctionDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToWeaponsLocker;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the weapon's locker.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to passagewayDeckB;
            aftCompanionwayDeckC:
                move alien to aftCompanionwayDeckB;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to aftCompanionwayDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to forwardCompanionwayDeckB;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckC;
            forwardCompanionwayDeckC:
                move alien to forwardStarboardJunctionDeckC;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to aftStarboardJunctionDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to weaponsLocker;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                iMonsterLoc++;
                if (iMonsterLoc > MONSTERTOTAL) iMonsterLoc = 0;
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef DESTROYOBJECTS;
                if (weaponsLocker.takenBaton == false) stunBaton.spitOn = true;
                if (weaponsLocker.takenArmor == false) trooperArmor.spitOn = true;
                #EndIf;
                passagewayDeckBDoor.&name-->8 = 'broken';
                passagewayDeckBDoor.&name-->9 = 'torn';
                weaponsLockerHatch.&name-->3 = 'broken';
                move weaponsLockerAcid to weaponsLocker;
                weaponsLocker.alienWrecked = true;
                return IsWeapLockDestroyed();
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToBridge;
        #Ifdef PRINTBACKEND;
            if (parent(alien) == bridge) print "^The alien waits on the bridge.^";
            else print "^The alien moves towards the bridge.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftCompanionwayDeckC;
            aftCompanionwayDeckC:
                move alien to aftStarboardJunctionDeckC;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to forwardStarboardJunctionDeckC;
            bridge:
                if (PlayerOnBridge()) {
                    if (player in computerRoom) player.inComputerRoom = true;
                    ! ***************************************************
                    ! Alien Waits For Player To Come Out Of Computer Room
                    ! ***************************************************
                } else {
                    ! *******************************************************************
                    ! Alien Missed Player, It Goes Back To The Same Room It Was Headed To
                    ! *******************************************************************
                    if (alien.waitOneTurn) {
                        alien.waitOneTurn = false;
                        iMonsterDestination = monster_loc-->iMonsterLoc;
                        move alien to galley;
                    }
                    alien.waitOneTurn = true;
                }
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to galley;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckA;
            forwardCompanionwayDeckC:
                move alien to forwardCompanionwayDeckB;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to forwardCompanionwayDeckC;
            galley:
                move alien to bridge;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToForwardStarboardJctnDeckC;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the Forward-Starboard Junction Deck C.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftCompanionwayDeckC;
            aftCompanionwayDeckC:
                move alien to aftStarboardJunctionDeckC;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to forwardStarboardJunctionDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to forwardCompanionwayDeckB;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckC;
            forwardCompanionwayDeckC:
                move alien to forwardStarboardJunctionDeckC;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef PRINTBACKEND;
                    "^The alien arrives at the Forward-Starboard Junction Deck C and looks around.";
                #EndIf;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToForwardCompanionwayDeckC;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the Forward Companionway Deck C.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftCompanionwayDeckC;
            aftCompanionwayDeckC:
                move alien to aftStarboardJunctionDeckC;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to forwardStarboardJunctionDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to forwardCompanionwayDeckB;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckC;
            forwardCompanionwayDeckC:
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef PRINTBACKEND;
                    "^The alien arrives at the Forward Companionway Deck C and looks around.";
                #EndIf;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to forwardCompanionwayDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToAftCompanionwayDeckC;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the Aft Companionway Deck C.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftCompanionwayDeckC;
            aftCompanionwayDeckC:
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef PRINTBACKEND;
                    "^The alien arrives at the Aft Companionway Deck C and looks around.";
                #EndIf;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to aftCompanionwayDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to forwardCompanionwayDeckB;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckC;
            forwardCompanionwayDeckC:
                move alien to forwardStarboardJunctionDeckC;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to aftStarboardJunctionDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to aftCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                move alien to forwardCompanionwayDeckA;
        }
  ];

  [ AlienToAftJunctionDeckA;
        #Ifdef PRINTBACKEND;
            print "^The alien moves towards the aft corridor - Deck A.^";
        #EndIf;
        switch (parent(alien)) {
            aftCompanionwayDeckB:
                move alien to aftCompanionwayDeckC;
            aftCompanionwayDeckC:
                move alien to aftStarboardJunctionDeckC;
            aftJunctionDeckB:
                move alien to aftCompanionwayDeckB;
            aftStarboardJunctionDeckC:
                move alien to forwardStarboardJunctionDeckC;
            captainsQuarters:
                move alien to galley;
            controlRoomDeckC:
                move alien to aftCompanionwayDeckC;
            crewLounge:
                move alien to forwardStarboardJunctionDeckB;
            foodLockerCorridorDeckB:
                move alien to aftCompanionwayDeckB;
            foodStorage:
                move alien to foodLockerCorridorDeckB;
            forwardCompanionwayDeckA:
                move alien to aftJunctionDeckA;
            forwardCompanionwayDeckB:
                move alien to forwardCompanionwayDeckA;
            forwardCompanionwayDeckC:
                move alien to forwardCompanionwayDeckB;
            forwardStarboardJunctionDeckB:
                move alien to foodLockerCorridorDeckB;
            forwardStarboardJunctionDeckC:
                move alien to forwardCompanionwayDeckC;
            galley:
                move alien to forwardCompanionwayDeckA;
            hypersleepVault:
                move alien to forwardCompanionwayDeckA;
            infirmary:
                move alien to forwardCompanionwayDeckA;
            maintenanceGarage:
                move alien to forwardCompanionwayDeckC;
            passagewayDeckB:
                move alien to forwardCompanionwayDeckB;
            portShuttleBay:
                move alien to aftJunctionDeckB;
            scienceCorridorDeckB:
                move alien to forwardCompanionwayDeckB;
            starboardShuttleBay:
                move alien to aftJunctionDeckB;
            weaponsLocker:
                move alien to passagewayDeckB;
            aftJunctionDeckA:
                iMonsterDestination = monster_loc-->iMonsterLoc;
                iAlienMovement = 0;
                #Ifdef PRINTBACKEND;
                    "^The alien arrives at the Aft Junction Deck A and looks around.";
                #EndIf;
        }
  ];

  [ IsInfirmaryDestroyed;
        if (infirmary.destroyedYet == false) {
            infirmary.destroyedYet = true;
            if (PlayerOnADeck()) {
                print "^From somewhere on this deck";
            } else {
                if (PlayerOnForeBDeck()) {
                    print "^From somewhere above you";
                } else {
                    print "^From somewhere above you, towards the front of the ship";
                }
            }
            print ", you hear the sound of wood and plastic crashing into one another. Then a
            pause, only to hear wood break and pop-off in succession. After the last beam is snapped, a
            high-pitched cry rings out";
            if (player.firstItemTaken) {
                player.firstItemTaken = false;
                ". You have a feeling you're not alone.";
            } else {
                ".";
            }
        }
        #Ifdef PRINTBACKEND;
        print "^The alien arrives at the infirmary and looks around.^";
        #EndIf;
        rtrue;
  ];

  [ IsVaultDestroyed;
        if (hypersleepVault.destroyedYet == false) {
            hypersleepVault.destroyedYet = true;
            if (PlayerOnADeck()) {
                print "^From somewhere on this deck";
            } else {
                if (PlayerOnForeBDeck()) {
                    print "^From somewhere above you";
                } else {
                    print "^From somewhere above you, towards the front of the ship";
                }
            }
            print ", a shattering crash rings throughout the ship. It's followed by the sound of containers
            being thrown around one of the rooms. When the thudding stops, a high-pitched cry follows";
            if (player.firstItemTaken) {
                player.firstItemTaken = false;
                ". You have a feeling you're not alone.";
            } else {
                ".";
            }
        }
        #Ifdef PRINTBACKEND;
        print "^The alien arrives at the hypersleep vault and looks around.^";
        #EndIf;
        rtrue;
  ];

  [ IsPortShuttleBayDestroyed;
        if (portShuttleBay.destroyedYet == false) {
            portShuttleBay.destroyedYet = true;
            print "^You jump at the sound of scratching knives that grate on your nerves. It rings out ";
            if (PlayerOnADeck()) {
                print "below you, towards the ship's aft end";
            } else {
                if (PlayerOnCDeck()) {
                    print "above you, towards the ship's aft end";
                } else {
                    if (PlayerOnBDeck()) {
                        print "on this deck";
                    } else {
                        print "on this deck, towards the ship's aft end";
                    }
                }
            }
            print ", like a thrashing of metal that fails to break. But, when it comes to an end, you ignore
            the chill in your bones";
            if (player.firstItemTaken) {
                player.firstItemTaken = false;
                ". You have a feeling you're not alone.";
            } else {
                ".";
            }
        }
        #Ifdef PRINTBACKEND;
        print "^The alien arrives at the port shuttle bay and looks around.^";
        #EndIf;
        rtrue;
  ];

  [ IsStarboardShuttleBayDestroyed;
        if (starboardShuttleBay.destroyedYet == false) {
            starboardShuttleBay.destroyedYet = true;
            if (starboardShuttleBay.takenSuit) {
                print "^You're startled by the sound of scratching and banging that echoes through the ship.
                The creatures rage being taken out on metal. It comes from the aft";
                if (PlayerOnADeck()) ", below you.";
                if (PlayerOnBDeck()) ", on this deck.";
                if (PlayerOnCDeck()) ", above you.";
                ".";
            }
            print "^You're startled by the sound of plastic being torn apart. The sound of synthetics
            being shredded. It comes from the aft portion of the ship";
            if (PlayerOnADeck()) print " below you";
            if (PlayerOnBDeck()) print " on this deck";
            if (PlayerOnCDeck()) print " above you";
            if (player.firstItemTaken) {
                player.firstItemTaken = false;
                ". You have a feeling you're not alone.";
            } else {
                ".";
            }
        }
        #Ifdef PRINTBACKEND;
        print "^The alien arrives at the starboard shuttle bay and looks around.^";
        #EndIf;
        rtrue;
  ];

  [ IsScienceCorridorDestroyed;
        if (player in instrumentationBay) scienceCorridorDeckB.destroyedYet = true;
        if (scienceCorridorDeckB.destroyedYet == false) {
            scienceCorridorDeckB.destroyedYet = true;
            if (PlayerOnADeck()) {
                print "^From somewhere below you";
            } else {
                if (PlayerOnCDeck()) {
                    print "^From somewhere above you";
                } else {
                    if (PlayerOnBDeck()) {
                        print "^From somewhere on this deck, towards the front end of the ship";
                    } else {
                        print "^From somewhere on this deck";
                    }
                }
            }
            print ", you're startled to hear a high-pitched scream coupled with a loud banging.
            The sounds echo through the empty derelict";
            if (player.firstItemTaken) {
                player.firstItemTaken = false;
                ". You have a feeling you're not alone.";
            } else {
                ".";
            }
        }
        #Ifdef PRINTBACKEND;
        print "^The alien arrives at the science corridor and looks around.^";
        #EndIf;
        rtrue;
  ];


  [ IsCaptainsQuartersDestroyed;
        if (captainsQuarters.destroyedYet == false) {
            captainsQuarters.destroyedYet = true;
            if (PlayerOnADeck()) {
                print "^From somewhere on this deck";
            } else {
                print "^From somewhere above you, towards the forward end of the ship";
            }
            print ", you hear the sound of wood being crushed in another room. Like it snapped in half.
            Then metal being thrown around? It's hard to tell";
            if (player.firstItemTaken) {
                player.firstItemTaken = false;
                ". You have a feeling you're not alone.";
            } else {
                ".";
            }
        }
        #Ifdef PRINTBACKEND;
        print "^The alien arrives at the captain's quarters and looks around.^";
        #EndIf;
        rtrue;
  ];

  [ IsMaintenanceGarageDestroyed;
        if (maintenanceGarage.destroyedYet == false) {
            maintenanceGarage.destroyedYet = true;
            if (player in clawChamber || player in forwardCompanionwayDeckC) {
                print "^From the room next to you";
            } else {
                if (PlayerOnCDeck()) {
                    print "^From somewhere on this deck";
                } else {
                    print "^From somewhere below you, towards the ship's forward end";
                }
            }
            print ", the sound of metal cracking in half echoes through the vessel with a force
            so strong you think you feel it before you hear it. The massive blast
            rings through the vessel, giving you pause";
            if (player.firstItemTaken) {
                player.firstItemTaken = false;
                ". You have a feeling you're not alone.";
            } else {
                ".";
            }
        }
        #Ifdef PRINTBACKEND;
        print "^The alien arrives at the maintenance garage and looks around.^";
        #EndIf;
        rtrue;
  ];

  [ IsControlRoomDestroyed;
        if (controlRoomDeckC.destroyedYet == false) {
            controlRoomDeckC.destroyedYet = true;
            if (PlayerOnCDeck()) {
                print "^From somewhere on this deck";
            } else {
                print "^From somewhere below you, towards the ship's aft end";
            }
            print ", the sound of cans being tossed around rings out. Then metal as it's bounced
            off the walls in one of the rooms. It ends with a bit of scraping and scratching";
            if (player.firstItemTaken) {
                player.firstItemTaken = false;
                ". You have a feeling you're not alone.";
            } else {
                ".";
            }
        }
        #Ifdef PRINTBACKEND;
        print "^The alien arrives at the control room and looks around.^";
        #EndIf;
        rtrue;
  ];

  [ IsLoungeDestroyed;
        if (crewLounge.destroyedYet == false) {
            crewLounge.destroyedYet = true;
            if (PlayerOnBDeck()) {
                print "^From somewhere on this deck";
            } else {
                if (PlayerOnADeck()) {
                    print "^From somewhere below you, towards the aft end of the ship";
                } else {
                    if (PlayerOnCDeck()) {
                        print "^From somewhere above you, towards the starboard side of the ship";
                    } else {
                        print "^From somewhere towards the aft end of the ship";
                    }
                }
            }
            print ", the sound of tearing and scratching, along with a high-pitched scream,
            reaches your ears. You cringe for a second as the spaceship rings hollow";
            if (player.firstItemTaken) {
                player.firstItemTaken = false;
                ". You have a feeling you're not alone.";
            } else {
                ".";
            }
        }
        #Ifdef PRINTBACKEND;
        print "^The alien arrives at the crew lounge and looks around.^";
        #EndIf;
        rtrue;
  ];

  [ IsWeapLockDestroyed;
        if (weaponsLocker.destroyedYet == false) {
            weaponsLocker.destroyedYet = true;
            if (player in passagewayDeckB)
                "^Like metal being torn in half, a ripping can be heard as half the smoke
                in the passageway gets sucked into the locker. Then a high-pitched scream follows.
                You feel the alien next to you, even though you can't see him.";
            if (PlayerOnBDeck()) {
                print "^From somewhere on this deck";
            } else {
                if (PlayerOnADeck()) {
                    print "^From somewhere below you, towards the aft end of the ship";
                } else {
                    if (PlayerOnCDeck()) {
                        print "^From somewhere above you, towards the port side of the ship";
                    } else {
                        print "^From somewhere towards the aft end of the ship";
                    }
                }
            }
            print ", a ripping can be heard before a loud thud rings through the vessel. Then a
            high-pitched scream follows. You listen for more, but the echoes die down";
            if (player.firstItemTaken) {
                player.firstItemTaken = false;
                ". You have a feeling you're not alone.";
            } else {
                ".";
            }
        }
        #Ifdef PRINTBACKEND;
        print "^The alien arrives at the weapon's locker and looks around.^";
        #EndIf;
        rtrue;
  ];

  [ IsFoodLockDestroyed;
        if (foodStorage.destroyedYet == false) {
            foodStorage.destroyedYet = true;
            if (player in foodLockerCorridorDeckB)
                "^It starts with a hammering that quickly builds before you hear a sharp pop,
                and the locker door goes flying down the passageway. Startled - you're lucky
                you didn't get hit. You feel the alien next to you, even though you can't see him.";
            if (PlayerOnBDeck()) {
                print "^From somewhere on this deck";
            } else {
                if (PlayerOnADeck()) {
                    print "^From somewhere below you, towards the aft end of the ship";
                } else {
                    if (PlayerOnCDeck()) {
                        print "^From somewhere above you, towards the starboard side of the ship";
                    } else {
                        print "^From somewhere towards the aft end of the ship";
                    }
                }
            }
            print ", it starts with a hammering that builds quickly before you hear a sharp pop.
            Like something cracked open. You listen for anything else, but the echo dies down";
            if (player.firstItemTaken) {
                player.firstItemTaken = false;
                ". You have a feeling you're not alone.";
            } else {
                ".";
            }
        }
        #Ifdef PRINTBACKEND;
        print "^The alien arrives at the food locker and looks around.^";
        #EndIf;
        rtrue;
  ];

  [ DistanceToAlien;
        ! ******
        ! Deck A
        ! ******
        ! # 1
        if (player in bridge) {
            if (alien in galley) return 1;
            if (alien in captainsQuarters) return 2;
            if (alien in forwardCompanionwayDeckA) return 2;
            if (alien in aftJunctionDeckA) return 3;
            if (alien in infirmary) return 3;
            if (alien in hypersleepVault) return 3;
            if (alien in forwardCompanionwayDeckB) return 3;
            if (alien in scienceCorridorDeckB) return 4;
            if (alien in forwardCompanionwayDeckC) return 4;
            return 0;
        }
        ! # 2
        if (player in computerRoom) {
            return 0;
        }
        ! # 3
        if (player in galley) {
            if (alien in bridge) return 1;
            if (alien in captainsQuarters) return 1;
            if (alien in forwardCompanionwayDeckA) return 1;
            if (alien in infirmary) return 2;
            if (alien in hypersleepVault) return 2;
            if (alien in aftJunctionDeckA) return 2;
            if (alien in forwardCompanionwayDeckB) return 2;
            if (alien in scienceCorridorDeckB) return 3;
            if (alien in forwardCompanionwayDeckC) return 3;
            if (alien in maintenanceGarage) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 4
        if (player in captainsQuarters) {
            if (alien in bridge) return 2;
            if (alien in galley) return 1;
            if (alien in forwardCompanionwayDeckA) return 2;
            if (alien in infirmary) return 3;
            if (alien in hypersleepVault) return 3;
            if (alien in aftJunctionDeckA) return 3;
            if (alien in forwardCompanionwayDeckB) return 3;
            if (alien in scienceCorridorDeckB) return 4;
            if (alien in forwardCompanionwayDeckC) return 4;
            return 0;
        }
        ! # 5
        if (player in infirmary) {
            if (alien in forwardCompanionwayDeckA) return 1;
            if (alien in galley) return 2;
            if (alien in hypersleepVault) return 2;
            if (alien in aftJunctionDeckA) return 2;
            if (alien in forwardCompanionwayDeckB) return 2;
            if (alien in bridge) return 3;
            if (alien in captainsQuarters) return 3;
            if (alien in scienceCorridorDeckB) return 3;
            if (alien in forwardCompanionwayDeckC) return 3;
            if (alien in maintenanceGarage) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 6
        if (player in forwardCompanionwayDeckA) {
            if (alien in infirmary) return 1;
            if (alien in hypersleepVault) return 1;
            if (alien in aftJunctionDeckA) return 1;
            if (alien in galley) return 1;
            if (alien in forwardCompanionwayDeckB) return 1;
            if (alien in bridge) return 2;
            if (alien in captainsQuarters) return 2;
            if (alien in scienceCorridorDeckB) return 2;
            if (alien in forwardCompanionwayDeckC) return 2;
            if (alien in maintenanceGarage) return 3;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 3;
            if (alien in aftStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 7
        if (player in hypersleepVault) {
            if (alien in forwardCompanionwayDeckA) return 1;
            if (alien in galley) return 2;
            if (alien in infirmary) return 2;
            if (alien in aftJunctionDeckA) return 2;
            if (alien in forwardCompanionwayDeckB) return 2;
            if (alien in bridge) return 3;
            if (alien in captainsQuarters) return 3;
            if (alien in scienceCorridorDeckB) return 3;
            if (alien in forwardCompanionwayDeckC) return 3;
            if (alien in maintenanceGarage) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 8
        if (player in aftJunctionDeckA) {
            if (alien in forwardCompanionwayDeckA) return 1;
            if (alien in galley) return 2;
            if (alien in infirmary) return 2;
            if (alien in hypersleepVault) return 2;
            if (alien in forwardCompanionwayDeckB) return 2;
            if (alien in bridge) return 3;
            if (alien in captainsQuarters) return 3;
            if (alien in scienceCorridorDeckB) return 3;
            if (alien in forwardCompanionwayDeckC) return 3;
            if (alien in maintenanceGarage) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 9
        if (player in personalLockerRoom) {
            if (alien in aftJunctionDeckA) return 1;
            if (alien in forwardCompanionwayDeckA) return 2;
            if (alien in galley) return 3;
            if (alien in infirmary) return 3;
            if (alien in hypersleepVault) return 3;
            if (alien in forwardCompanionwayDeckB) return 3;
            if (alien in bridge) return 4;
            if (alien in captainsQuarters) return 4;
            if (alien in scienceCorridorDeckB) return 4;
            if (alien in forwardCompanionwayDeckC) return 4;
            return 0;
        }
        ! **********************************************
        ! Player Can Not Hear Below The Maintenance Lift
        ! **********************************************
        ! # 10
        if (player in maintenanceLiftDeckA) {
            if (alien in aftJunctionDeckA) return 1;
            if (alien in forwardCompanionwayDeckA) return 2;
            if (alien in galley) return 3;
            if (alien in infirmary) return 3;
            if (alien in hypersleepVault) return 3;
            if (alien in forwardCompanionwayDeckB) return 3;
            if (alien in bridge) return 4;
            if (alien in captainsQuarters) return 4;
            if (alien in scienceCorridorDeckB) return 4;
            if (alien in forwardCompanionwayDeckC) return 4;
            return 0;
        }
        ! **************
        ! Forward Deck B
        ! **************
        ! # 11
        if (player in forwardCorridorDeckB) {
            if (alien in forwardCompanionwayDeckB) return 2;
            if (alien in scienceCorridorDeckB) return 3;
            if (alien in forwardCompanionwayDeckA) return 3;
            if (alien in forwardCompanionwayDeckC) return 3;
            if (alien in aftJunctionDeckA) return 4;
            if (alien in infirmary) return 4;
            if (alien in hypersleepVault) return 4;
            if (alien in galley) return 4;
            if (alien in maintenanceGarage) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 12
        if (player in starboardJunctionDeckB) {
            if (alien in forwardCompanionwayDeckB) return 1;
            if (alien in scienceCorridorDeckB) return 2;
            if (alien in forwardCompanionwayDeckA) return 2;
            if (alien in forwardCompanionwayDeckC) return 2;
            if (alien in infirmary) return 3;
            if (alien in hypersleepVault) return 3;
            if (alien in galley) return 3;
            if (alien in aftJunctionDeckA) return 3;
            if (alien in captainsQuarters) return 4;
            if (alien in bridge) return 4;
            if (alien in maintenanceGarage) return 3;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 3;
            if (alien in aftStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 13
        if (player in forwardCompanionwayDeckB) {
            if (alien in scienceCorridorDeckB) return 1;
            if (alien in forwardCompanionwayDeckA) return 1;
            if (alien in forwardCompanionwayDeckC) return 1;
            if (alien in infirmary) return 2;
            if (alien in hypersleepVault) return 2;
            if (alien in galley) return 2;
            if (alien in aftJunctionDeckA) return 2;
            if (alien in captainsQuarters) return 3;
            if (alien in bridge) return 3;
            if (alien in maintenanceGarage) return 2;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 2;
            if (alien in aftStarboardJunctionDeckC) return 3;
            if (alien in aftCompanionwayDeckC) return 4;
            return 0;
        }
        ! # 14
        if (player in scienceCorridorDeckB) {
            if (alien in forwardCompanionwayDeckB) return 1;
            if (alien in forwardCompanionwayDeckA) return 2;
            if (alien in forwardCompanionwayDeckC) return 2;
            if (alien in infirmary) return 3;
            if (alien in hypersleepVault) return 3;
            if (alien in galley) return 3;
            if (alien in captainsQuarters) return 4;
            if (alien in bridge) return 4;
            if (alien in maintenanceGarage) return 3;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 3;
            if (alien in aftStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 15
        if (player in instrumentationBay) {
            if (alien in scienceCorridorDeckB) return 1;
            if (alien in forwardCompanionwayDeckB) return 2;
            if (alien in forwardCompanionwayDeckA) return 3;
            if (alien in forwardCompanionwayDeckC) return 3;
            if (alien in infirmary) return 4;
            if (alien in hypersleepVault) return 4;
            if (alien in galley) return 4;
            if (alien in aftJunctionDeckA) return 4;
            if (alien in maintenanceGarage) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! **********
        ! Aft Deck B
        ! **********
        ! **********************************************
        ! Player Can Not Hear Above The Maintenance Lift
        ! - Can Not Hear Into Deck A
        ! **********************************************
        ! # 16
        if (player in maintenanceLiftDeckB) {
            if (alien in passagewayDeckB) return 2;
            if (alien in weaponsLocker) return 3;
            if (alien in aftCompanionwayDeckB) return 3;
            if (alien in foodLockerCorridorDeckB) return 4;
            if (alien in aftCompanionwayDeckC) return 4;
            if (alien in aftJunctionDeckB) return 4;
            return 0;
        }
        ! # 17
        if (player in forwardPortJunctionDeckB) {
            if (alien in passagewayDeckB) return 1;
            if (alien in weaponsLocker) return 2;
            if (alien in aftCompanionwayDeckB) return 2;
            if (alien in foodLockerCorridorDeckB) return 3;
            if (alien in aftCompanionwayDeckC) return 3;
            if (alien in aftJunctionDeckB) return 3;
            if (alien in foodStorage) return 4;
            if (alien in forwardStarboardJunctionDeckB) return 4;
            if (alien in portShuttleBay) return 4;
            if (alien in starboardShuttleBay) return 4;
            if (alien in controlRoomDeckC) return 4;
            if (alien in aftStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 18
        if (player in forwardStarboardJunctionDeckB) {
            if (alien in crewLounge) return 1;
            if (alien in foodLockerCorridorDeckB) return 1;
            if (alien in foodStorage) return 2;
            if (alien in aftCompanionwayDeckB) return 2;
            if (alien in passagewayDeckB) return 3;
            if (alien in aftJunctionDeckB) return 3;
            if (alien in aftCompanionwayDeckC) return 3;
            if (alien in weaponsLocker) return 4;
            if (alien in portShuttleBay) return 4;
            if (alien in starboardShuttleBay) return 4;
            if (alien in controlRoomDeckC) return 4;
            if (alien in aftStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 19
        if (player in crewLounge) {
            if (alien in forwardStarboardJunctionDeckB) return 1;
            if (alien in foodLockerCorridorDeckB) return 2;
            if (alien in foodStorage) return 3;
            if (alien in aftCompanionwayDeckB) return 3;
            if (alien in passagewayDeckB) return 4;
            if (alien in aftJunctionDeckB) return 4;
            if (alien in aftCompanionwayDeckC) return 4;
            return 0;
        }
        ! # 20
        if (player in weaponsLocker) {
            if (alien in passagewayDeckB) return 1;
            if (alien in aftCompanionwayDeckB) return 2;
            if (alien in foodLockerCorridorDeckB) return 3;
            if (alien in aftJunctionDeckB) return 3;
            if (alien in aftCompanionwayDeckC) return 3;
            if (alien in foodStorage) return 4;
            if (alien in forwardStarboardJunctionDeckB) return 4;
            if (alien in portShuttleBay) return 4;
            if (alien in starboardShuttleBay) return 4;
            if (alien in controlRoomDeckC) return 4;
            if (alien in aftStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 21
        if (player in passagewayDeckB) {
            if (alien in weaponsLocker) return 1;
            if (alien in aftCompanionwayDeckB) return 1;
            if (alien in foodLockerCorridorDeckB) return 2;
            if (alien in aftJunctionDeckB) return 2;
            if (alien in aftCompanionwayDeckC) return 2;
            if (alien in foodStorage) return 3;
            if (alien in forwardStarboardJunctionDeckB) return 3;
            if (alien in portShuttleBay) return 3;
            if (alien in starboardShuttleBay) return 3;
            if (alien in controlRoomDeckC) return 3;
            if (alien in aftStarboardJunctionDeckC) return 3;
            if (alien in crewLounge) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 22
        if (player in aftCompanionwayDeckB) {
            if (alien in passagewayDeckB) return 1;
            if (alien in foodLockerCorridorDeckB) return 1;
            if (alien in aftJunctionDeckB) return 1;
            if (alien in aftCompanionwayDeckC) return 1;
            if (alien in foodStorage) return 2;
            if (alien in weaponsLocker) return 2;
            if (alien in forwardStarboardJunctionDeckB) return 2;
            if (alien in portShuttleBay) return 2;
            if (alien in starboardShuttleBay) return 2;
            if (alien in controlRoomDeckC) return 2;
            if (alien in aftStarboardJunctionDeckC) return 2;
            if (alien in crewLounge) return 3;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 3;
            if (alien in forwardCompanionwayDeckC) return 4;
            return 0;
        }
        ! # 23
        if (player in foodLockerCorridorDeckB) {
            if (alien in foodStorage) return 1;
            if (alien in aftCompanionwayDeckB) return 1;
            if (alien in forwardStarboardJunctionDeckB) return 1;
            if (alien in crewLounge) return 2;
            if (alien in passagewayDeckB) return 2;
            if (alien in aftJunctionDeckB) return 2;
            if (alien in aftCompanionwayDeckC) return 2;
            if (alien in weaponsLocker) return 3;
            if (alien in portShuttleBay) return 3;
            if (alien in starboardShuttleBay) return 3;
            if (alien in controlRoomDeckC) return 3;
            if (alien in aftStarboardJunctionDeckC) return 3;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 24
        if (player in foodStorage) {
            if (alien in foodLockerCorridorDeckB) return 1;
            if (alien in forwardStarboardJunctionDeckB) return 2;
            if (alien in aftCompanionwayDeckB) return 2;
            if (alien in aftCompanionwayDeckC) return 3;
            if (alien in passagewayDeckB) return 3;
            if (alien in crewLounge) return 3;
            if (alien in controlRoomDeckC) return 4;
            if (alien in aftStarboardJunctionDeckC) return 4;
            if (alien in weaponsLocker) return 4;
            if (alien in portShuttleBay) return 4;
            if (alien in starboardShuttleBay) return 4;
            return 0;
        }
        ! # 25
        if (player in portShuttleBay) {
            if (alien in aftJunctionDeckB) return 1;
            if (alien in starboardShuttleBay) return 2;
            if (alien in aftCompanionwayDeckB) return 2;
            if (alien in passagewayDeckB) return 3;
            if (alien in aftCompanionwayDeckC) return 3;
            if (alien in foodLockerCorridorDeckB) return 3;
            if (alien in forwardStarboardJunctionDeckB) return 4;
            if (alien in aftStarboardJunctionDeckC) return 4;
            if (alien in controlRoomDeckC) return 4;
            if (alien in weaponsLocker) return 4;
            if (alien in foodStorage) return 4;
            return 0;
        }
        ! # 26
        if (player in aftJunctionDeckB) {
            if (alien in portShuttleBay) return 1;
            if (alien in starboardShuttleBay) return 1;
            if (alien in aftCompanionwayDeckB) return 1;
            if (alien in passagewayDeckB) return 2;
            if (alien in aftCompanionwayDeckC) return 2;
            if (alien in foodLockerCorridorDeckB) return 2;
            if (alien in forwardStarboardJunctionDeckB) return 3;
            if (alien in aftStarboardJunctionDeckC) return 3;
            if (alien in controlRoomDeckC) return 3;
            if (alien in weaponsLocker) return 3;
            if (alien in foodStorage) return 3;
            if (alien in crewLounge) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 27
        if (player in starboardShuttleBay) {
            if (alien in aftJunctionDeckB) return 1;
            if (alien in portShuttleBay) return 2;
            if (alien in aftCompanionwayDeckB) return 2;
            if (alien in passagewayDeckB) return 3;
            if (alien in aftCompanionwayDeckC) return 3;
            if (alien in foodLockerCorridorDeckB) return 3;
            if (alien in forwardStarboardJunctionDeckB) return 4;
            if (alien in aftStarboardJunctionDeckC) return 4;
            if (alien in controlRoomDeckC) return 4;
            if (alien in weaponsLocker) return 4;
            if (alien in foodStorage) return 4;
            return 0;
        }
        ! ******
        ! Deck C
        ! ******
        ! # 28
        if (player in forwardCompanionwayDeckC) {
            ! ***************************************************************************************
            ! Player Can't Hear The Alien If the Pipes Are Blown In Forward Starboard Junction Deck C
            ! - It's Too Loud
            ! ***************************************************************************************
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in maintenanceGarage) return 1;
            if (alien in forwardStarboardJunctionDeckC) return 1;
            if (alien in forwardCompanionwayDeckB) return 1;
            if (alien in scienceCorridorDeckB) return 2;
            if (alien in forwardCompanionwayDeckA) return 2;
            if (alien in aftStarboardJunctionDeckC) return 2;
            if (alien in aftCompanionwayDeckC) return 3;
            if (alien in infirmary) return 3;
            if (alien in galley) return 3;
            if (alien in aftJunctionDeckA) return 3;
            if (alien in hypersleepVault) return 3;
            if (alien in bridge) return 4;
            if (alien in captainsQuarters) return 4;
            if (alien in controlRoomDeckC) return 4;
            if (alien in aftCompanionwayDeckB) return 4;
            return 0;
        }
        ! # 29
        if (player in forwardStarboardJunctionDeckC) {
            if (alien in forwardCompanionwayDeckC) return 1;
            if (alien in aftStarboardJunctionDeckC) return 1;
            if (alien in forwardCompanionwayDeckB) return 2;
            if (alien in maintenanceGarage) return 2;
            if (alien in aftCompanionwayDeckC) return 2;
            if (alien in aftCompanionwayDeckB) return 3;
            if (alien in scienceCorridorDeckB) return 3;
            if (alien in forwardCompanionwayDeckA) return 3;
            if (alien in controlRoomDeckC) return 3;
            if (alien in infirmary) return 4;
            if (alien in galley) return 4;
            if (alien in hypersleepVault) return 4;
            if (alien in aftJunctionDeckA) return 4;
            if (alien in passagewayDeckB) return 4;
            if (alien in foodLockerCorridorDeckB) return 4;
            if (alien in aftJunctionDeckB) return 4;
            return 0;
        }
        ! # 30
        if (player in maintenanceGarage) {
            if (alien in forwardCompanionwayDeckC) return 1;
            if (alien in forwardCompanionwayDeckB) return 2;
            if (alien in scienceCorridorDeckB) return 3;
            if (alien in forwardCompanionwayDeckA) return 3;
            if (alien in infirmary) return 4;
            if (alien in hypersleepVault) return 4;
            if (alien in galley) return 4;
            if (alien in aftJunctionDeckA) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 2;
            if (alien in aftStarboardJunctionDeckC) return 3;
            if (alien in aftCompanionwayDeckC) return 4;
            return 0;
        }
        ! # 31
        if (player in clawChamber) {
            if (alien in maintenanceGarage) return 1;
            if (alien in forwardCompanionwayDeckC) return 2;
            if (alien in forwardCompanionwayDeckB) return 3;
            if (alien in forwardCompanionwayDeckA) return 4;
            if (alien in scienceCorridorDeckB) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 3;
            if (alien in aftStarboardJunctionDeckC) return 4;
            return 0;
        }
        ! # 32
        if (player in aftPortJunctionDeckC) {
            if (alien in aftCompanionwayDeckC) return 1;
            if (alien in controlRoomDeckC) return 2;
            if (alien in aftStarboardJunctionDeckC) return 2;
            if (alien in aftCompanionwayDeckB) return 2;
            if (alien in aftJunctionDeckB) return 3;
            if (alien in passagewayDeckB) return 3;
            if (alien in foodLockerCorridorDeckB) return 3;
            if (alien in portShuttleBay) return 4;
            if (alien in starboardShuttleBay) return 4;
            if (alien in foodStorage) return 4;
            if (alien in weaponsLocker) return 4;
            if (alien in forwardStarboardJunctionDeckB) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 3;
            if (alien in forwardCompanionwayDeckC) return 4;
            return 0;
        }
        ! # 33
        if (player in aftCompanionwayDeckC) {
            if (alien in controlRoomDeckC) return 1;
            if (alien in aftStarboardJunctionDeckC) return 1;
            if (alien in aftCompanionwayDeckB) return 1;
            if (alien in aftJunctionDeckB) return 2;
            if (alien in passagewayDeckB) return 2;
            if (alien in foodLockerCorridorDeckB) return 2;
            if (alien in weaponsLocker) return 3;
            if (alien in foodStorage) return 3;
            if (alien in portShuttleBay) return 3;
            if (alien in starboardShuttleBay) return 3;
            if (alien in forwardStarboardJunctionDeckB) return 3;
            if (alien in crewLounge) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 2;
            if (alien in forwardCompanionwayDeckC) return 3;
            if (alien in forwardCompanionwayDeckB) return 4;
            if (alien in maintenanceGarage) return 4;
            return 0;
        }
        ! # 34
        if (player in aftStarboardJunctionDeckC) {
            ! ***************************************************************************************
            ! Player Can't Hear The Alien If the Pipes Are Blown In Forward Starboard Junction Deck C
            ! - It's Too Loud
            ! ***************************************************************************************
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in aftCompanionwayDeckC) return 1;
            if (alien in forwardStarboardJunctionDeckC) return 1;
            if (alien in controlRoomDeckC) return 2;
            if (alien in aftCompanionwayDeckB) return 2;
            if (alien in forwardCompanionwayDeckC) return 2;
            if (alien in forwardCompanionwayDeckB) return 3;
            if (alien in forwardCompanionwayDeckA) return 4;
            if (alien in maintenanceGarage) return 3;
            if (alien in aftJunctionDeckB) return 3;
            if (alien in passagewayDeckB) return 3;
            if (alien in foodLockerCorridorDeckB) return 3;
            if (alien in scienceCorridorDeckB) return 4;
            if (alien in portShuttleBay) return 4;
            if (alien in starboardShuttleBay) return 4;
            if (alien in foodStorage) return 4;
            if (alien in weaponsLocker) return 4;
            if (alien in forwardStarboardJunctionDeckB) return 4;
            return 0;
        }
        ! # 35
        if (player in controlRoomDeckC) {
            if (alien in aftCompanionwayDeckC) return 1;
            if (alien in aftStarboardJunctionDeckC) return 2;
            if (alien in aftCompanionwayDeckB) return 2;
            if (alien in aftJunctionDeckB) return 3;
            if (alien in passagewayDeckB) return 3;
            if (alien in foodLockerCorridorDeckB) return 3;
            if (alien in portShuttleBay) return 4;
            if (alien in starboardShuttleBay) return 4;
            if (alien in foodStorage) return 4;
            if (alien in weaponsLocker) return 4;
            if (alien in forwardStarboardJunctionDeckB) return 4;
            if (forwardStarboardJunctionDeckC.pipesBlown) return 0;
            if (alien in forwardStarboardJunctionDeckC) return 3;
            if (alien in forwardCompanionwayDeckC) return 4;
            return 0;
        }
        return 0;
  ];

  [ DirectionAlienIsIn;
        ! ******
        ! Deck A
        ! ******
        ! # 1
        if (player in bridge) {
            return RETURN_AFT;
        }
        ! # 2
        if (player in computerRoom) {
            return RETURN_PORT;
        }
        ! # 3
        if (player in galley) {
            if (alien in bridge) return RETURN_FORWARD;
            if (alien in captainsQuarters) return RETURN_STARBOARD;
            return RETURN_AFT;
        }
        ! # 4
        if (player in captainsQuarters) {
            return RETURN_PORT;
        }
        ! # 5
        if (player in infirmary) {
            return RETURN_STARBOARD;
        }
        ! # 6
        if (player in forwardCompanionwayDeckA) {
            if (alien in infirmary) return RETURN_PORT;
            if (alien in hypersleepVault) return RETURN_STARBOARD;
            if (alien in galley) return RETURN_FORWARD;
            if (alien in bridge) return RETURN_FORWARD;
            if (alien in captainsQuarters) return RETURN_FORWARD;
            return RETURN_BELOW;
        }
        ! # 7
        if (player in hypersleepVault) {
            return RETURN_PORT;
        }
        ! # 8
        if (player in aftJunctionDeckA) {
            return RETURN_FORWARD;
        }
        ! # 9
        if (player in personalLockerRoom) {
            return RETURN_PORT;
        }
        ! # 10
        if (player in maintenanceLiftDeckA) {
          return RETURN_STARBOARD;
        }
        ! **************
        ! Forward Deck B
        ! **************
        ! # 11
        if (player in forwardCorridorDeckB) {
            return RETURN_AFT;
        }
        ! # 12
        if (player in starboardJunctionDeckB) {
            return RETURN_PORT;
        }
        ! # 13
        if (player in forwardCompanionwayDeckB) {
            if (alien in scienceCorridorDeckB) return RETURN_FORWARD;
            if (alien in forwardCompanionwayDeckA) return RETURN_ABOVE;
            if (alien in infirmary) return RETURN_ABOVE;
            if (alien in hypersleepVault) return RETURN_ABOVE;
            if (alien in galley) return RETURN_ABOVE;
            if (alien in captainsQuarters) return RETURN_ABOVE;
            if (alien in bridge) return RETURN_ABOVE;
            return RETURN_BELOW;
        }
        ! # 14
        if (player in scienceCorridorDeckB) {
            return RETURN_AFT;
        }
        ! # 15
        if (player in instrumentationBay) {
            return RETURN_STARBOARD;
        }
        ! **********
        ! Aft Deck B
        ! **********
        ! # 16
        if (player in maintenanceLiftDeckB) {
            return RETURN_STARBOARD;
        }
        ! # 17
        if (player in forwardPortJunctionDeckB) {
            return RETURN_AFT;
        }
        ! # 18
        if (player in forwardStarboardJunctionDeckB) {
            if (alien in crewLounge) return RETURN_STARBOARD;
            return RETURN_AFT;
        }
        ! # 19
        if (player in crewLounge) {
            return RETURN_PORT;
        }
        ! # 20
        if (player in weaponsLocker) {
            return RETURN_STARBOARD;
        }
        ! # 21
        if (player in passagewayDeckB) {
            if (alien in weaponsLocker) return RETURN_PORT;
            return RETURN_STARBOARD;
        }
        ! # 22
        if (player in aftCompanionwayDeckB) {
            if (alien in weaponsLocker) return RETURN_PORT;
            if (alien in passagewayDeckB) return RETURN_PORT;
            if (alien in crewLounge) return RETURN_STARBOARD;
            if (alien in foodStorage) return RETURN_STARBOARD;
            if (alien in foodLockerCorridorDeckB) return RETURN_STARBOARD;
            if (alien in forwardStarboardJunctionDeckB) return RETURN_STARBOARD;
            if (alien in portShuttleBay) return RETURN_AFT;
            if (alien in aftJunctionDeckB) return RETURN_AFT;
            if (alien in starboardShuttleBay) return RETURN_AFT;
            return RETURN_BELOW;
        }
        ! # 23
        if (player in foodLockerCorridorDeckB) {
            if (alien in foodStorage) return RETURN_STARBOARD;
            if (alien in forwardStarboardJunctionDeckB) return RETURN_FORWARD;
            if (alien in crewLounge) return RETURN_FORWARD;
            return RETURN_PORT;
        }
        ! # 24
        if (player in foodStorage) {
            return RETURN_PORT;
        }
        ! # 25
        if (player in portShuttleBay) {
            return RETURN_STARBOARD;
        }
        ! # 26
        if (player in aftJunctionDeckB) {
            if (alien in portShuttleBay) return RETURN_PORT;
            if (alien in starboardShuttleBay) return RETURN_STARBOARD;
            return RETURN_FORWARD;
        }
        ! # 27
        if (player in starboardShuttleBay) {
            return RETURN_PORT;
        }
        ! ******
        ! Deck C
        ! ******
        ! # 28
        if (player in forwardCompanionwayDeckC) {
            if (alien in maintenanceGarage) return RETURN_AFT;
            if (alien in forwardStarboardJunctionDeckC) return RETURN_STARBOARD;
            if (alien in aftStarboardJunctionDeckC) return RETURN_STARBOARD;
            if (alien in aftCompanionwayDeckC) return RETURN_STARBOARD;
            if (alien in controlRoomDeckC) return RETURN_STARBOARD;
            if (alien in aftCompanionwayDeckB) return RETURN_STARBOARD;
            return RETURN_ABOVE;
        }
        ! # 29
        if (player in forwardStarboardJunctionDeckC) {
            if (alien in galley) return RETURN_PORT;
            if (alien in infirmary) return RETURN_PORT;
            if (alien in hypersleepVault) return RETURN_PORT;
            if (alien in scienceCorridorDeckB) return RETURN_PORT;
            if (alien in forwardCompanionwayDeckC) return RETURN_PORT;
            if (alien in forwardCompanionwayDeckB) return RETURN_PORT;
            if (alien in forwardCompanionwayDeckA) return RETURN_PORT;
            return RETURN_AFT;
        }
        ! # 30
        if (player in maintenanceGarage) {
            return RETURN_FORWARD;
        }
        ! # 31
        if (player in clawChamber) {
            return RETURN_FORWARD;
        }
        ! # 32
        if (player in aftPortJunctionDeckC) {
            return RETURN_STARBOARD;
        }
        ! # 33
        if (player in aftCompanionwayDeckC) {
            if (alien in controlRoomDeckC) return RETURN_AFT;
            if (alien in aftStarboardJunctionDeckC) return RETURN_STARBOARD;
            if (alien in forwardStarboardJunctionDeckC) return RETURN_STARBOARD;
            if (alien in maintenanceGarage) return RETURN_STARBOARD;
            if (alien in forwardCompanionwayDeckB) return RETURN_STARBOARD;
            if (alien in forwardCompanionwayDeckC) return RETURN_STARBOARD;
            return RETURN_ABOVE;
        }
        ! # 34
        if (player in aftStarboardJunctionDeckC) {
            if (alien in maintenanceGarage) return RETURN_FORWARD;
            if (alien in forwardCompanionwayDeckC) return RETURN_FORWARD;
            if (alien in forwardCompanionwayDeckB) return RETURN_FORWARD;
            if (alien in forwardCompanionwayDeckA) return RETURN_FORWARD;
            if (alien in forwardStarboardJunctionDeckC) return RETURN_FORWARD;
            return RETURN_PORT;
        }
        ! # 35
        if (player in controlRoomDeckC) {
            return RETURN_FORWARD;
        }
  ];

  [ IncreaseAlienSpeed;
        #Ifdef PRINTBACKEND;
            print "^Alien Speed: ", iAlienSpeed, "^";
        #EndIf;
        iIncreaseSpeed++;
        if (iIncreaseSpeed > SPEEDINCREASE) {
            iIncreaseSpeed = 0;
            iAlienSpeed--;
            if (iAlienSpeed < 35) iAlienSpeed = 35;
        }
  ];


  ! *************************
  ! This Tests For A Deck
  ! *************************
  [ AlienOnADeck;
        if (alien in galley) rtrue;
        if (alien in captainsQuarters) rtrue;
        if (alien in infirmary) rtrue;
        if (alien in forwardCompanionwayDeckA) rtrue;
        if (alien in hypersleepVault) rtrue;
        if (alien in aftJunctionDeckA) rtrue;
        rfalse;
  ];

  ! ***********************************************
  ! This Tests If Alien Is In Range Of The Elevator
  ! ***********************************************
  [ AlienCloseToElevator;
        if (alien in bridge) rtrue;
        if (alien in forwardCompanionwayDeckA) rtrue;
        if (alien in galley) rtrue;
        if (alien in infirmary) rtrue;
        if (alien in forwardCompanionwayDeckB) rtrue;
        if (alien in captainsQuarters) rtrue;
        if (alien in scienceCorridorDeckB) rtrue;
        if (alien in forwardCompanionwayDeckC) rtrue;
        if (alien in maintenanceGarage) rtrue;
        if (forwardStarboardJunctionDeckC.pipesBlown) rfalse;
        if (alien in forwardStarboardJunctionDeckC) rtrue;
        rfalse;
  ];

  ! *************************
  ! This Tests For Aft B Deck
  ! *************************
  [ AlienOnBDeck;
        if (alien in forwardStarboardJunctionDeckB) rtrue;
        if (alien in crewLounge) rtrue;
        if (alien in weaponsLocker) rtrue;
        if (alien in passagewayDeckB) rtrue;
        if (alien in aftCompanionwayDeckB) rtrue;
        if (alien in foodLockerCorridorDeckB) rtrue;
        if (alien in foodStorage) rtrue;
        if (alien in portShuttleBay) rtrue;
        if (alien in aftJunctionDeckB) rtrue;
        if (alien in starboardShuttleBay) rtrue;
        rfalse;
  ];

  [ AlienOnCDeck;
        if (alien in forwardCompanionwayDeckC) rtrue;
        if (alien in forwardStarboardJunctionDeckC) rtrue;
        if (alien in maintenanceGarage) rtrue;
        if (alien in aftCompanionwayDeckC) rtrue;
        if (alien in aftStarboardJunctionDeckC) rtrue;
        if (alien in controlRoomDeckC) rtrue;
        rfalse;
  ];

  [ AlienAboveCDeck;
        if (alien in scienceCorridorDeckB) rtrue;
        if (alien in forwardCompanionwayDeckB) rtrue;
        if (alien in bridge) rtrue;
        if (alien in galley) rtrue;
        if (alien in captainsQuarters) rtrue;
        if (alien in infirmary) rtrue;
        if (alien in forwardCompanionwayDeckA) rtrue;
        if (alien in hypersleepVault) rtrue;
        rfalse;
  ];
