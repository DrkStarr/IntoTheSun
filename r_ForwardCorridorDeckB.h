
! ---------------------------------------------------------------------------- !
!       FORWARD CORRIDOR DECK B. 10/08/21
!
  Room    forwardCorridorDeckB "Forward Corridor - Deck B"
   with   description [;
              if (self.firstTime) {
                  self.firstTime = false;
                  iRoom++;
                  "Thick smoke makes it hard to see as you step into the corridor from the airlock.
                  Finally, your eyes adjust to the dim light. In front of you is a body spread across
                  the deck. Something cut him in half, pulling his entrails out. The man is no longer
                  alive, but an object lies close to an outstretched hand.^
                  ^A cattle prod is just a few feet away from the dead body.";
              }
              if (self.advncG) {
                  self.advncG = false;
              } else {
                  player.advanceGravity = false;
              }
              player.inCorridor = true;
              print "Thick smoke makes it hard to see the dead body spread across the deck - guts ripped
              out by a heavy blow, now hardened in place. The dim lights radiate an orange glow, bouncing
              off the smoke and reflecting a pale color.^^Forward, the airlock will take you to your ship.
              To the aft, you can head deeper into the derelict";
              if (cattleProd in self) ".^^A cattle prod is just a few feet away from the dead body.";
              ".";
          ],
          n_to [;
              <<Enter forwardCorridorDeckBAirlock>>;
          ],
          s_to [;
              if (cattleProd in self) {
                  cattleProd.taken = false;
                  move cattleProd to player;
                  print "You pick up the cattle prod just in case - damn, what did this guy encounter?^";
              } else {
                  if (self.steppedAround == false) {
                      self.steppedAround = true;
                      print "You step around the body heading aft.^";
                  }
              }
              self.advncG = true;
              return starboardJunctionDeckB;
          ],
          cant_go [;
              "You can go forward back to your ship or aft deeper into the derelict.";
          ],
          before [;
              Exit:
                  <<Enter forwardCorridorDeckBAirlock>>;
              Listen:

          ],
          advncG false,
          firstTime true,
          steppedAround false;

! 10/08/21

  RoomObj -> forwardCorridorDeckBObj "corridor"
    with  name 'corridor' 'area' 'passageway' 'passage' 'place',
          description [;
              <<Look forwardCorridorDeckB>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the corridor.";
          ];

! 10/13/21

  Object  -> forwardCorridorDeckBBody "dead body"
    with  name 'dead' 'body' 'guy' 'man' 'dude' 'gut' 'guts' 'skeleton' 'entrails' 'bone' 'bones',
          before [;
              Attack:
                  if (second == cattleProd) "If you hit the skeleton, you'd waste a charge. There's nothing left but bone. The skeleton doesn't even have muscles to make it twitch.";
                  if (second == nothing) "There's no need to beat on the skeleton. The bones are brittle, and you would only pulverize them.";
                  "There's no need to hit the skeleton with that. The bones are brittle, and you would only pulverize them.";
              Prod:
                  if (cattleProd in player) "If you hit the skeleton, you'd waste a charge. There's nothing left but bone. The skeleton doesn't even have muscles to make it twitch.";
              Examine:
                  player.advanceGravity = false;
                  "Looking closer at the body, it's really a skeleton whose flesh melted off long ago.
                  This man has been here for decades. Before he died, it seems like he was reaching for
                  the cattle prod but didn't make it.";
              Go:
                  "You are already here.";
              default:
                  "The skeleton's dead. Leave him be.";
          ],
          life [;
              "The skeleton's dead. Leave him be.";
          ],
          orders [;
              "The skeleton's dead. Leave him be.";
          ],
    has   static concealed;

! 10/13/21

  StObj   -> forwardCorridorDeckBAirlock "airlock"
    with  name 'airlock' 'main' 'door',
          before [ rTest;
              Examine:
                  player.advanceGravity = false;
                  "Written across the door, it says MAIN AIRLOCK: AUTHORIZED PERSONNEL ONLY. It's connected to the docking ring and leads back to your ship.";
              Go:
                  "You are already here.";
              Enter:
                  if (iGravityForce < 3) {
                      print "Are you sure you want to disembark the ship? ";
                      rTest = YesOrNo();
                      if (rTest) print "^";
                  } else {
                      rTest = true;
                  }
                  if (rTest) {
                      if (self.playerNeverLeavesRoom) {
                          print "You leave the derelict behind. Whatever happened here isn't worth risking your life.^";
                      } else {
                          if (EndGameLoot()) {
                              if (LootAmount() == false) print "You leave the derelict behind. Happy to make it out alive though discouraged by what little loot you could find.^";
                              else {
                                  if (GreatRun() == false) print "You leave the derelict behind. Happy to make it out alive with the loot you could find.^";
                                  else print "You leave the derelict behind. This was a great run, and you're happy to make it out alive.^";
                              }
                          } else {
                              print "You leave the derelict behind. Happy to make it out alive.^";
                          }
                      }
                      return EndGamePayout();
                  }
                  rtrue;
              Open:
                  if (self.playerNeverLeavesRoom) {
                      print "Opening the airlock, you leave the derelict behind. Whatever happened here isn't worth risking your life.^";
                  } else {
                      if (EndGameLoot()) {
                          if (LootAmount() == false) print "Opening the airlock, you leave the derelict behind. Happy to make it out alive though discouraged by what little loot you could find.^";
                          else {
                              if (GreatRun() == false) print "Opening the airlock, you leave the derelict behind. Happy to make it out alive with the loot you could find.^";
                              else print "Opening the airlock, you leave the derelict behind. This was a great run, and you're happy to make it out alive.^";
                          }
                      } else {
                          print "Opening the airlock, you leave the derelict behind. Happy to make it out alive.^";
                      }
                  }
                  return EndGamePayout();
          ],
          playerNeverLeavesRoom true;

! 10/14/21

  StObj   forwardCorridorDeckBLight "lights"
    with  name 'dim' 'light' 'lights' 'glow' 'soft' 'amber' 'led' 'leds' 'orange' 'pale' 'color',
          before [;
              Examine:
                  player.advanceGravity = false;
                  print "The lights in this area try to cut through the smoke but only give off a soft amber glow. The ship must be in power conservation mode";
                  if (self.seenLights) ".";
                  self.seenLights = true;
                  ". The batteries have all but run out.";
              Go:
                  "You are already here.";
          ],
          seenLights false,
          found_in forwardCorridorDeckB starboardJunctionDeckB forwardCompanionwayDeckB scienceCorridorDeckB
                   maintenanceLiftDeckB passagewayDeckB forwardStarboardJunctionDeckB foodLockerCorridorDeckB
                   aftCompanionwayDeckB aftJunctionDeckB portShuttleBay starboardShuttleBay
                   forwardCompanionwayDeckC  forwardStarboardJunctionDeckC aftPortJunctionDeckC aftStarboardJunctionDeckC
                   aftCompanionwayDeckC maintenanceGarage forwardCompanionwayDeckA galley captainsQuarters
                   hypersleepVault aftJunctionDeckA;

! 10/14/21

  StObj   forwardCorridorDeckBDerelict "derelict"
    with  name 'derelict' 'ship' 'vessel' 'tug',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "This vessel is ancient. She's been drifting through space for a long time. So you'd say the old girl has at least 100 years on her. Probably 150.";
              Go:
                  "You are already here.";
          ],
          found_in forwardCorridorDeckB starboardJunctionDeckB forwardCompanionwayDeckB scienceCorridorDeckB
                   maintenanceLiftDeckB passagewayDeckB forwardStarboardJunctionDeckB foodLockerCorridorDeckB
                   aftCompanionwayDeckB aftJunctionDeckB portShuttleBay starboardShuttleBay
                   forwardCompanionwayDeckC  forwardStarboardJunctionDeckC aftPortJunctionDeckC aftStarboardJunctionDeckC
                   aftCompanionwayDeckC maintenanceGarage forwardCompanionwayDeckA galley  captainsQuarters
                   infirmary hypersleepVault aftJunctionDeckA;

! 10/17/21

  StObj   forwardCorridorDeckBSmoke "smoke"
    with  name 'smoke' 'air' 'haze' 'hazy' 'thick' 'gloom' 'dark' 'cloud' 'smog' 'dense' 'muck' 'acidic',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The smoke hangs heavy throughout the vessel. Something blew and has contaminated the entire ship.";
              Enter, Go:
                  "You need to tell me which direction to go in.";
          ],
          found_in forwardCorridorDeckB forwardCompanionwayDeckB scienceCorridorDeckB
                   maintenanceLiftDeckB passagewayDeckB forwardStarboardJunctionDeckB foodLockerCorridorDeckB
                   aftCompanionwayDeckB
                   forwardCompanionwayDeckC  forwardStarboardJunctionDeckC aftPortJunctionDeckC aftStarboardJunctionDeckC
                   aftCompanionwayDeckC forwardCompanionwayDeckA galley  captainsQuarters
                   infirmary hypersleepVault aftJunctionDeckA;

! 10/26/21

  StObj   forwardCorridorDeckBBulkhead "bulkheads"
    with  name 'bulkhead' 'bulkheads' 'wall' 'walls',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Bulkheads are nothing more than the walls of the ship - sturdy - this vessel was made to last.";
              Go:
                  "You are already here.";
              Take, Push, Pull, PushDir, Turn:
                  "The bulkheads aren't going anywhere.";
          ],
          found_in forwardCorridorDeckB starboardJunctionDeckB forwardCompanionwayDeckB
                   maintenanceLiftDeckB passagewayDeckB forwardStarboardJunctionDeckB foodLockerCorridorDeckB
                   aftCompanionwayDeckB aftJunctionDeckB portShuttleBay starboardShuttleBay
                   forwardCompanionwayDeckC  forwardStarboardJunctionDeckC aftPortJunctionDeckC aftStarboardJunctionDeckC
                   aftCompanionwayDeckC maintenanceGarage forwardCompanionwayDeckA galley
                   infirmary hypersleepVault aftJunctionDeckA,
    has   pluralname;

! 10/31/21

  OutRch  forwardCorridorDeckBVent "vent"
    with  name 'vent' 'ventilation' 'vents' 'system',
          before [;
              Enter:
                  "You wouldn't last long in there.";
              Examine:
                  player.advanceGravity = false;
                  "The ventilation system runs throughout the ship. It was used to supply the vessel with fresh air
                  when it was in working condition, but the scrubbers are blown. The ship's full of smoke.";
              Go:
                  "You are as close as you're going to get.";
          ],
          found_in forwardCorridorDeckB starboardJunctionDeckB scienceCorridorDeckB
                   maintenanceLiftDeckB passagewayDeckB forwardStarboardJunctionDeckB foodLockerCorridorDeckB
                   aftCompanionwayDeckB aftJunctionDeckB portShuttleBay starboardShuttleBay
                   forwardCompanionwayDeckC  forwardStarboardJunctionDeckC aftPortJunctionDeckC aftStarboardJunctionDeckC
                   aftCompanionwayDeckC maintenanceGarage forwardCompanionwayDeckA galley  captainsQuarters
                   infirmary hypersleepVault aftJunctionDeckA;

! 11/07/21

  StObj   frwrdCrrdrDckBLght "lights"
    with  name 'dim' 'light' 'lights' 'glow' 'soft' 'amber' 'led' 'leds' 'orange' 'pale' 'color',
          before [;
              Examine:
                  player.advanceGravity = false;
                  print "The lights in this area try to cut through the smoke but only give off a soft amber glow. The ship must be in power conservation mode";
                  if (forwardCorridorDeckBLight.seenLights) ".";
                  forwardCorridorDeckBLight.seenLights = true;
                  ". The batteries have all but run out.";
              Go:
                  "You are already here.";
          ],
          found_in personalLockerRoom controlRoomDeckC instrumentationBay clawChamber
                   forwardPortJunctionDeckB crewLounge;

! 11/07/21

  StObj   frwrdCrrdrDckBDrlct "derelict"
    with  name 'derelict' 'ship' 'vessel' 'tug',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "This vessel is ancient. She's been drifting through space for a long time. So you'd say the old girl has at least 100 years on her. Probably 150.";
              Go:
                  "You are already here.";
          ],
          found_in personalLockerRoom controlRoomDeckC maintenanceLiftDeckA instrumentationBay clawChamber bridge
                   computerRoom foodStorage weaponsLocker forwardPortJunctionDeckB crewLounge;

! 11/07/21

  StObj   frwrdCrrdrDckBSmk "smoke"
    with  name 'smoke' 'air' 'haze' 'hazy' 'thick' 'gloom' 'dark' 'cloud' 'smog' 'dense' 'muck' 'acidic',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The smoke hangs heavy throughout the vessel. Something blew and has contaminated the entire ship.";
              Enter, Go:
                  "You need to tell me which direction to go in.";
          ],
          found_in personalLockerRoom controlRoomDeckC
                   forwardPortJunctionDeckB crewLounge;

! 11/07/21

  StObj   frwrdCrrdrDckBBlkhd "bulkheads"
    with  name 'bulkhead' 'bulkheads' 'wall' 'walls',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Bulkheads are nothing more than the walls of the ship - sturdy - this vessel was made to last.";
              Go:
                  "You are already here.";
              Take, Push, Pull, PushDir, Turn:
                  "The bulkheads aren't going anywhere.";
          ],
          found_in personalLockerRoom controlRoomDeckC maintenanceLiftDeckA instrumentationBay clawChamber bridge
          computerRoom foodStorage weaponsLocker forwardPortJunctionDeckB crewLounge,
    has   pluralname;

! 11/07/21

  OutRch  frwrdCrrdrDckBVnt "vent"
    with  name 'vent' 'ventilation' 'vents' 'system',
          before [;
              Enter:
                  "You wouldn't last long in there.";
              Examine:
                  player.advanceGravity = false;
                  "The ventilation system runs throughout the ship. It was used to supply the vessel with fresh air
                  when it was in working condition, but the scrubbers are blown. The ship's full of smoke.";
              Go:
                  "You are as close as you're going to get.";
          ],
          found_in personalLockerRoom controlRoomDeckC maintenanceLiftDeckA instrumentationBay clawChamber bridge
                   computerRoom foodStorage weaponsLocker forwardPortJunctionDeckB crewLounge;
