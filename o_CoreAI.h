
! ---------------------------------------------------------------------------- !
!       CORE AI. 01/04/22
!

Object  coreAI "core AI"
  with  name 'core' 'ai' 'brain' 'electric',
        before [;
            Attack:
                "Are you really going to break the stuff you're trying to loot?";
            Burn:

            Drop:
                if (self in player || self in vortexBag) "You don't want to do that. You can at least try to sell it later.";
            Go:
                "You are already here.";
            Insert:
                if (second == dataReader) {
                    if (self in computerRoomPanel) {
                        move self to vortexBag;
                        "That doesn't fit in there, so you move it to the vortex bag.";
                    } else {
                        "That doesn't fit in there.";
                    }
                }
                if (second == computerRoomPanel)
                    "You gutted the AI. It can't be put back into the computer.";
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Examine, Search:
                player.advanceGravity = false;
                "The core AI is sealed in a titanium case. A row of small lights runs down the side
                with only one rapidly blinking, showing the electric brain is low on power.";
            Kick:

            Take:
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                move self to vortexBag;
                self.takenSelf = true;
                remove bridgeGlow;
                computerRoom.terminalHasPower = false;
                bridgeLights.&name-->8 = 'glow';
                "You take ", (the) self, ", pulling on strands of wire that connect the electric brain to the computer.
                The lights surrounding you die. The ship is left to what little battery power is left. Without the AI
                guiding the energy, it will burn up fast. You put the core into the vortex bag.";
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            Close, Open:
                "It doesn't work like that. You slide flashcards in and out of it.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        print "You can't quickly get to ", (the) self, ".";
                        return StandingDeath();
                    }
                }
        ],
        takenSelf false;
