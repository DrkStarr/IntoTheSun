
! ---------------------------------------------------------------------------- !
!       SCIENCE CORRIDOR DECK B. 10/23/21
!
  Room    scienceCorridorDeckB "Science Corridor - Deck B"
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
              player.inCorridor = true;
              print "This vessel is equipped with many sensors, covering everything from gravimetric distortions
              to audio anomalies, and this corridor housed all the monitoring stations for the science department.
              But an explosion happened here, destroying the passage and blocking it when the bulkheads collapsed. ";
              if (scienceCorridorDeckBHatch.hatchOpen) print "There's a hatch to port that's been forced open.";
              else print "There's a hatch to port, but the blast broke off the handle.";
              if (scienceCorridorDeckBHatch.hatchOpen) "^^With the hatch open, you can go aft or port.";
              "^^Since you are boxed in like this, you can only go aft to the companionway.";
          ],
          w_to [;
              if (alien in self) return PXF();
              <<Enter scienceCorridorDeckBHatch>>;
          ],
          s_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return forwardCompanionwayDeckB;
          ],
          cant_go [;
              if (alien in self) return PXF();
              if (scienceCorridorDeckBHatch.hatchOpen) "You can go aft or port.";
              "You can go aft to the companionway.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(forwardCompanionwayDeckB, 2);
                  rtrue;
              GoIn:
                  if (alien in self) return PXF();
                  if (scienceCorridorDeckBHatch.hatchOpen) {
                      self.firstTime = true;
                      return PlayerTo(instrumentationBay, 2);
                  }
              Listen:
                  if (forwardStarboardJunctionDeckC.pipesBlown) "Aft, you hear the faint sound of gas venting into the air.";
          ],
          destroyedYet false,
          roomCount true,
          firstTime true;

! 10/23/21

  RoomObj -> scienceCorridorDeckBObj "corridor"
    with  name 'corridor' 'area' 'passageway' 'passage' 'place',
          description [;
              <<Look scienceCorridorDeckB>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the corridor.";
          ];

! 10/23/21

  OutRch  -> scienceCorridorDeckBCompanionway "companionway"
    with  name 'companionway',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "You can't see it through the smoke, but the companionway is aft.";
              Enter, Go:
                  if (alien in scienceCorridorDeckB) return PXF();
                  scienceCorridorDeckB.firstTime = true;
                  PlayerTo(forwardCorridorDeckB, 2);
                  rtrue;
          ];

! 10/23/21

  StObj   -> scienceCorridorDeckBBulkhead "bulkhead"
    with  name 'debris' 'rubble' 'trash' 'metal' 'reinforced' 'support' 'supports' 'shrapnel' 'blast' 'bulkhead' 'wall' 'explosion' 'scrap' 'junk',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "Bulkheads collapsed when the explosion went off, with reinforced supports colliding
                  as shrapnel went everywhere. Now there's no way forward.";
              Go:
                  "You are already here.";
              Take, Push, Pull, PushDir, Turn:
                  "The bulkhead isn't going anywhere. It's a mess of scrap metal.";
          ];

! 10/23/21

  StObj   -> scienceCorridorDeckBBulkeads "bulkheads"
    with  name 'supports' 'bulkheads',
          before [;
              Examine:
                  <<Examine scienceCorridorDeckBBulkhead>>;
              Go:
                  <<Go scienceCorridorDeckBBulkhead>>;
              Take, Push, Pull, PushDir, Turn:
                  "The bulkheads aren't going anywhere. That's a mess of scrap metal.";
          ],
      has pluralname;

! 10/23/21

  NoHelp   -> scienceCorridorDeckBHatch "hatch"
    with  name 'hatch' 'door' 'handle' 'bay' 'room',
          before [ iTempLoc;
              Attack:
                  if (self.hatchOpen) "You don't need to do that. The hatch has already been forced open.";
                  if (second == sledgehammer) {
                      if (sledgehammer in vortexBag) {
                          move sledgehammer to player;
                          if (cattleProd in player) move cattleProd to vortexBag;
                          print "(first taking the sledgehammer)^";
                      }
                      self.hatchOpen = true;
                      iMonsterDestination = SCIENCECRRDR;
                      iTempLoc = iMonsterLoc;
                      iTempLoc++;
                      if (iTempLoc > MONSTERTOTAL) iTempLoc = 0;
                      monster_loc-->iTempLoc = SCIENCECRRDR;
                      alien.resetLocInCorridor = true;
                      print "Swinging it with all you got, the metal connects with a loud blast that rings throughout the ship.
                      The hatch gives, and you watch it swing open.^^";
                      if (AlienOnADeck()) "A cry from the deck above answers as you open the hatch.";
                      if (AlienOnBDeck()) "A cry from the aft portion of this deck answers as you open the hatch.";
                      if (AlienOnCDeck()) "A cry from below answers as you open the hatch.";
                      "A cry, close by, rings out, giving you pause.";
                  }
                  if (second == crowbar) {
                      if (crowbar in vortexBag) {
                          move crowbar to player;
                          print "(first taking the crowbar)^";
                      }
                      "You could try beating on the hatch with the crowbar, but it would only call the xenomorph.";
                  }
                  if (second == cattleProd) {
                      if (cattleProd in vortexBag) {
                          move cattleProd to player;
                          if (sledgehammer in player) move sledgehammer to vortexBag;
                          print "(first taking the cattle prod)^";
                      }
                      "You wouldn't even dent the hatch with something so thin. It needs to have more mass.";
                  }
                  if (second == dataReader) "The hatch is blasted closed. You'd only attract the xenomorph doing that.";
                  if (second == battery) "The hatch is blasted closed. You'd only attract the xenomorph doing that.";
                  if (second == redFlashcard) "The hatch is blasted closed. You'd only attract the xenomorph doing that.";
                  if (second == yellowFlashcard) "The hatch is blasted closed. You'd only attract the xenomorph doing that.";
                  if (second == vortexBag || second == outfit) {
                      if (alien.sleeping) "The hatch is blasted closed. You shouldn't distrub the ship.";
                      "The hatch is blasted closed. You'd only attract the xenomorph doing that.";
                  }
                  "It will will take more force than that. Hitting it with your hands isn't going to help.";
              Close:
                  if (self.hatchOpen) "It's not going to close that easily. You forced it open.";
                  "That's already closed.";
              Examine:
                  player.advanceGravity = false;
                  if (self.hatchOpen) "You forced open the hatch and now smoke slowly spills into the room.";
                  "The explosion did a number on everything in this hallway, scarring the door and blowing off the handle.
                  It doesn't look like there's an easy way to open it.";
              Enter:
                  if (alien in scienceCorridorDeckB) return PXF();
                  if (self.hatchOpen) {
                      scienceCorridorDeckB.firstTime = true;
                      return PlayerTo(instrumentationBay, 2);
                  }
                  "You try the hatch, but the explosion sealed it in place.";
              Kick, Push, Pull:
                  "That's not enough force to break it open.";
              Open:
                  if (self.hatchOpen) "You forced open the hatch and now smoke slowly spills into the room.";
                  "The hatch is broken, sealed by an explosion that crippled this corridor.";
              Go:
                  "You are already here.";
              Unlock:
                  if (self.hatchOpen) "You don't need to do that. The hatch has already been forced open.";
                  if (second == crowbar) {
                      if (crowbar in vortexBag) {
                          print "(first taking the crowbar)^";
                          move crowbar to player;
                      }
                      self.hatchOpen = true;
                      iMonsterDestination = SCIENCECRRDR;
                      iTempLoc = iMonsterLoc;
                      iTempLoc++;
                      if (iTempLoc > MONSTERTOTAL) iTempLoc = 0;
                      monster_loc-->iTempLoc = SCIENCECRRDR;
                      alien.resetLocInCorridor = true;
                      "You put the crowbar between the hatch and bulkhead, trying with all your might to open it.
                      The metal doesn't want to give, so you lean into it, pushing as hard as you can. Then a loud
                      crack sounds throughout the ship. The door gives, finally allowing access to the bay.";
                  }
                  if (second == sledgehammer) <<Attack self second>>;
                  if (second == cattleProd)
                      "The cattle prod isn't strong enough to force open the hatch. The metal rod is designed
                      to deliver a lot of voltage but wouldn't handle the pressure from the hatch and only snap.";
          ],
          hatchOpen false;

! 05/13/22

  OutRch  -> scienceCorridorDeckBSensors "sensors"
    with  name 'sensor' 'sensors',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The sensors are in the monitoring stations, and the explosion has blocked
                  access to all of them. You can't get through the debris.";
          ],
      has pluralname;

! 05/13/22

  OutRch  -> scienceCorridorDeckBStaions "stations"
    with  name 'stations',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "Blocked off by debris that has filled the corridor, you can't get to the monitoring stations.";
          ],
      has pluralname;

! 05/13/22

  OutRch  -> scienceCorridorDeckBStaion "station"
    with  name 'station' 'monitoring' 'equipment',
          before [;
              Examine:
                  <<Examine scienceCorridorDeckBStaions>>;
          ];
