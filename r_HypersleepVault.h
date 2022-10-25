
! ---------------------------------------------------------------------------- !
!       HYPERSLEEP VAULT. 11/02/21
!
  Room    hypersleepVault "Hypersleep Vault - Deck A"
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
              if (self.alienWrecked) {
                  "Smoke makes it hard to see in this oval room. The hibernation pods have
                  been torn apart with the doors ripped off. Compartment covers lie all around.
                  All of it is covered in acid.^^There's not a lot in this room besides the
                  destroyed pods in the middle. So you can exit to port.";
              }
              "This oval room has seven pods in the center, each facing inward and open. The lights inside
              the compartments fail to work, making the room darker than it should be. Except for the smoke,
              the space looks like it's kept sanitized. Nothing litters the smooth edge of the walls.^^There's
              not a lot in this room besides the pods in the middle. So you can exit to port.";
          ],
          w_to [;
              if (alien in self) return PXF();
              self.firstTime = true;
              return forwardCompanionwayDeckA;
          ],
          cant_go [;
              if (alien in self) return PXF();
              "You can exit port.";
          ],
          before [;
              Exit:
                  if (alien in self) return PXF();
                  self.firstTime = true;
                  PlayerTo(forwardCompanionwayDeckA, 2);
                  rtrue;
              Listen:

          ],
          alienWrecked false,
          destroyedYet false,
          takenNecklace false,
          roomCount true,
          firstTime true;

! 11/02/21

  RoomObj -> hypersleepVaultObj "vault"
    with  name 'vault' 'area' 'place' 'oval' 'room' 'section' 'chamber',
          description [;
              <<Look hypersleepVault>>;
          ],
          before [;
              Take, Remove, Turn, PushDir, Push, Pull:
                  "You can't do that to the vault.";
          ];

! 01/11/22

  StObj   -> hypersleepVaultPod "pod"
    with  name 'pod' 'shell' 'cover' 'compartment' 'hibernation' 'door' 'clear' 'window',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  if (hypersleepVault.alienWrecked) "You take a closer look at one of the pods, seeing it's covered in acid that burns through the shell.";
                  print "You take a closer look at one of the pods. The cover has a clear window built into it, so the person sleeping in the compartment can be seen. Looking inside, you see some liquid lying on the bottom";
                  if (necklace in hypersleepVault) ". Hanging off the edge, a silver necklace catches the orange glow of the lights.";
                  ".";
              Enter:
                  if (hypersleepVault.alienWrecked) "It's covered in acid. You would burn yourself horribly if you touched that.";
                  "The pod is open. You could get inside, but the solution is wet, and you're not going to be able to hide here.";
              Go:
                  "You are already here.";
              Open:
                  if (hypersleepVault.alienWrecked) "It's covered in acid. You would burn yourself horribly if you touched that.";
                  "The pod is already open.";
              Take, Remove:
                  if (hypersleepVault.alienWrecked) "It's covered in acid. You would burn yourself horribly if you touched that.";
                  "The pod is long and fits into the bag, but it's also worthless.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (hypersleepVault.alienWrecked) "It's covered in acid. You would burn yourself horribly if you touched that.";
                  return PNL();
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (hypersleepVault.alienWrecked) "It's covered in acid. You would burn yourself horribly if you touched that.";
                  return PNL();

          ];

! 01/11/22

  StObj   -> hypersleepVaultPods "pods"
    with  name 'pods' 'shells' 'covers' 'hibernation' 'doors',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  if (hypersleepVault.alienWrecked)
                      "The pods have been tossed around the room, covers torn off, then covered in an acid that boils through the shells.";
                  "The pods are laid out in a circle, facing inward. There's just enough space between the chambers
                  for each crew member to get ready before and after hypersleep.";
              Go:
                  "You are already here.";
              Take, Remove:
                  if (hypersleepVault.alienWrecked) "It's covered in acid. You would burn yourself horribly if you touched that.";
                  "The pods are long and fit into the bag, but they're also worthless.";
              Enter:
                  if (hypersleepVault.alienWrecked) "It's covered in acid. You would burn yourself horribly if you touched that.";
                  "The pods are open. You could get inside, but the solution is wet, and you're not going to be able to hide here.";
              Open:
                  if (hypersleepVault.alienWrecked) "It's covered in acid. You would burn yourself horribly if you touched that.";
                  "The pods are already open.";
              Attack, Burn, Climb, Close, Cut, Dig, Drink, Eat, Empty, Enter, Exit, GetOff, Go, GoIn, JumpOver, Kick, Listen, LookUnder, Open:
                  if (hypersleepVault.alienWrecked) "It's covered in acid. You would burn yourself horribly if you touched that.";
                  return PNL();
              Push, PushDir, Pull, Remove, Rub, Search, Set, SetTo, Smell, Squeeze, Swing, SwitchOn, SwitchOff, Take, Talk, Taste, Tie, Touch, Transfer, Turn, Unlock, Wave:
                  if (hypersleepVault.alienWrecked) "It's covered in acid. You would burn yourself horribly if you touched that.";
                  return PNL();

          ],
     has  pluralname;

! 01/11/22

  StObj   -> hypersleepVaultSolution "liquid"
    with  name 'thick' 'solution' 'liquid' 'clear' 'hypersleep' 'fluid',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "The liquid at the bottom of the pod is clear hypersleep fluid, and it slowly moves back and forth as the derelict floats through space.";
              Go:
                  "You are already here.";
              Taste, Drink, Eat:
                  "During hypersleep, a naked body laid in this liquid. If you could smell, you'd think twice about that.";
              Take, Remove, Touch, Rub:
                  "The germs have only multiplied since a naked body has laid in this fluid. You don't want to touch that. It's gross.";
          ],
     has  static concealed;

! 01/05/22

  AcidObj hypersleepVaultAcid "acid"
    with  name 'acid' 'pool' 'secretion' 'secretions',
          before [;
              Examine, Search:
                  player.advanceGravity = false;
                  "The acid burns everything it touches, trying to melt all the way through the deck.";
              Go:
                  "You are already here.";
          ];
