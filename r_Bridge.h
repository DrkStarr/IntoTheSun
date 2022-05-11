
! ---------------------------------------------------------------------------- !
!       BRIDGE. 11/12/21
!
  Room    bridge "Bridge - Deck A"
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
              print "Automated doors keep the smoke out - the air's clear. But all the lights are
              amber - there's little left in the batteries. The command chairs are empty, and the
              monitors that hang down from the ceiling are blank.";
              if (computerRoom.terminalHasPower) {
                  print " But there's a glow coming from the ";
                  if (bridgeHatch.hatchOpen) print "broken ";
                  print "hatch that's starboard. The A.I. is still alive after all these years.";
              }
              "^^There's a hatch that goes starboard to the computer room - while the automated
              doors head aft, back to the ship.";
          ],
          s_to [;
              if (alien in self) return PXF();
              <<Enter bridgeDoors>>;
          ],
          e_to [;
              <<Enter bridgeHatch>>;
          ],
          cant_go [;
              if (alien in self) return PXF();
              if (bridgeHatch.hatchOpen) "You can go aft or starboard.";
              "You can exit aft.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  print "The doors quickly close behind you as you enter the galley.^";
                  self.firstTime = true;
                  PlayerTo(galley, 2);
                  rtrue;
              Listen:

              GoIn:
                  if (bridgeHatch.hatchOpen) <<Enter bridgeHatch>>;
              SitRoom:
                  <<Enter bridgeChairs>>;
          ],
          takenTrinket false,
          roomCount true,
          firstTime true;

! 11/12/21

  RoomObj -> bridgeObj "bridge"
    with  name 'bridge' 'area' 'place' 'room',
          description [;
              <<Look bridge>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the bridge.";
          ];

! 11/16/21

  NoHelp  -> bridgeHatch "hatch"
    with  name 'hatch' 'groove' 'door',
          before [;
              Attack:
                  if (self.hatchOpen) "You don't need to do that. The hatch has already been forced open.";
                  if (second == sledgehammer) {
                      if (stunBaton in player) move stunBaton to vortexBag;
                      self.hatchOpen = true;
                      iMonsterDestination = BRDG;
                      if (sledgehammer in vortexBag) {
                          move sledgehammer to player;
                          if (stunBaton in player) move stunBaton to vortexBag;
                          if (cattleProd in player) move cattleProd to vortexBag;
                          print "(first taking the sledgehammer)^";
                      }
                      print "Something might be on this ship, but you have to know what is behind this hatch.
                      Swinging the sledgehammer, you feel the metal connect as it rings hollow - but the door
                      doesn't give. So you try again. And again. It finally pops open as a cry from ";
                      if (AlienOnADeck()) "this deck answers. The xenomorph is close.";
                      "deep within the ship answers.";
                  }
                  if (second == stunBaton) {
                      if (stunBaton.alreadyAttacked) "You hit the door with the stun baton, but there's no juice in it. It bounces off with a dull thud.";
                      "You don't want to discharge the stun baton. What little juice is left inside you might need.";
                  }
                  if (second == crowbar) {
                      iMonsterDestination = BRDG;
                      "Hitting the hatch with the crowbar does no damage. But the hollow sound rings
                      throughout the ship, attracting the alien.";
                  }
                  if (second == cattleProd) {
                      if (AlienOnADeck()) iMonsterDestination = BRDG;
                      "Hitting the hatch with the cattle prod does no damage, but it might attract the alien.";
                  }
                  if (second == dataReader) "The hatch is sealed. It isn't going to open that easily.";
                  if (second == battery) "The hatch is sealed. It isn't going to open that easily.";
                  if (second == redFlashcard) "The hatch is sealed. It isn't going to open that easily.";
                  if (second == yellowFlashcard) "The hatch is sealed. It isn't going to open that easily.";
                  if (second == outfit) "The hatch is sealed. It isn't going to open that easily.";
                  if (second == vortexBag) "The hatch is sealed. It isn't going to open that easily.";
                  "Using your hands, you beat on the sealed hatch. It isn't going to open that easily.";
              Close:
                  if (self.hatchOpen) "It's not going to close. You forced it open.";
                  "That's already closed.";
              Examine:
                  player.advanceGravity = false;
                  if (self.hatchOpen) "The hatch has been forced open. You now have access to the computer room.";
                  "It's a utility hatch that needs an access card to open. But you doubt that you'd be able to
                  find one on the ship since you haven't found one yet. There must be another way.";
              Enter:
                  if (alien in bridge) return PXF();
                  if (self.hatchOpen) {
                      bridge.firstTime = true;
                      return PlayerTo(computerRoom, 2);
                  }
                  "You try the hatch, but there's no simple way to open it.";
              Kick, Push, Pull:
                  "That's not enough force to break it open.";
              Open:
                  if (self.hatchOpen) "The hatch has been forced open. You now have access to the computer room.";
                  "There's only one way to operate the hatch, a slot for an access card. It's not as simple
                  as entering a code. But you doubt that you'd be able to find a card on the ship. You haven't
                  found one yet. There must be another way.";
              Go:
                  "You are already here.";
              Unlock:
                  if (self.hatchOpen) "You don't need to do that. The hatch has already been forced open.";
                  if (second == sledgehammer) <<Attack self second>>;
                  if (second == crowbar) {
                      if (crowbar in vortexBag) {
                          print "(first taking the crowbar)^";
                          move crowbar to player;
                      }
                      "The groove around the hatch is thin. The whole thing recessed into the bulkhead. So there's
                      no way to get a grip on it.";
                  }
                  if (second == kabar) {
                      "The ka-bar is a relic, not a tool. It will be worth much more unblemished.";
                  }
          ],
          hatchOpen false;

! 01/12/22

  StObj   -> bridgeDoors "automated doors"
    with  name 'automated' 'doors',
          before [;
              Close:
                  "They're already closed.";
              Examine:
                  player.advanceGravity = false;
                  "The automated doors to the bridge are unlocked and react to anyone who wants in or out.";
              Enter:
                  if (alien in bridge) return PXF();
                  print "The doors quickly close behind you as you enter the galley.^";
                  bridge.firstTime = true;
                  PlayerTo(galley, 2);
                  rtrue;
              Open:
                  "The doors are automatic, hence the name automated.";
              Go:
                  "You are already here.";
              Unlock:
                  "The doors are already unlocked. If you want to use them, enter them.";
          ],
     has  pluralname;

! 01/12/22

  StObj   -> bridgeChairs "chairs"
    with  name 'chair' 'chairs',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "There are four command chairs on the bridge. You are unsure about the stations, but there has to be one for navigation, ops, the executive officer, and the captain.";
              Enter:
                  "This is no time to relax. You are plunging into the sun.";
              Go:
                  "You are already here.";
          ],
     has  pluralname;

! 01/12/22

  StObj   -> bridgeStations "stations"
    with  name 'station' 'stations' 'navigation' 'ops' 'executive' 'officer' 'officer^s' 'captain' 'captain^s',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "There's no need to look over any of the stations. There's nothing valuable you're going to pull out of one.";
              Go:
                  "You are already here.";
          ],
     has  pluralname;

! 01/12/22

  StObj   -> bridgeMonitors "monitors"
    with  name 'monitor' 'monitors',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "All the monitors are as black as space. There is no information displayed. There is no power going to them.";
              Go:
                  "You are already here.";
              SwitchOn, SwitchOff:
                  "The A.I. handles that.";
          ],
     has  pluralname;

! 01/13/22

  StObj   -> bridgeLights "lights"
    with  name 'dim' 'light' 'lights' 'soft' 'amber' 'led' 'leds' 'orange' 'ph004',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "The lights up here are dim but give off a soft amber glow.";
              Go:
                  "You are already here.";
          ];

! 01/13/22

  StObj   -> bridgeGlow "glow"
    with  name 'glow',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "A glow radiates from the hatch starboard. There is still life in the A.I.";
              Go:
                  "You are already here.";
          ];

! 01/13/22

  StObj   -> bridgeSmoke "smoke"
    with  name 'smoke' 'air' 'haze' 'hazy' 'thin' 'gloom' 'dark' 'cloud' 'smog',
          before [;
              Examine:
                  player.advanceGravity = false;
                  "There's not a lot of smoke up here on the bridge. The automated doors keep it out.";
              Enter, Go:
                  "You need to tell me which direction to go in.";
          ];
