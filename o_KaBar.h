
! ---------------------------------------------------------------------------- !
!       KABAR. 11/04/21
!

Object  kabar "ka-bar"
  with  name 'combat' 'knife' 'ka-bar' 'engraved' 'usmc' 'old' 'military' 'relic',
        describe [;
            if (self in captainsQuarters) {
                if (self.spitOn) "^Lying next to the desk, an old ka-bar melts in some of the acid.";
                "^Lying on the bed is an old ka-bar, a combat knife engraved with USMC.";
            }
            rtrue;
        ],
        before [;
            Attack:
                if (self.spitOn) "Doused with acid, hitting that would be a bad idea. It would splash on your arms, melting through flesh and bone.";
                "Are you really going to break the stuff you're trying to loot?";
            Burn:

            Drop:
                if (self in vortexBag) {
                    print "(first taking ", (the) self, " from the vortex bag)^";
                    "You should leave it in the vortex bag. You'll be able to sell it later.";
                }
            Go:
                "You are already here.";
            Insert:
                if (self.spitOn) "Doused with acid, you would burn yourself if you tried that.";
                if (second == dataReader) {
                    if (captainsQuarters.takenKaBar) {
                        "That doesn't fit in there.";
                    } else {
                        move self to vortexBag;
                        captainsQuarters.takenKaBar = true;
                        print "That doesn't fit in there, so you move it to the vortex bag.^";
                        return ItemFirstTaken();
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    captainsQuarters.takenKaBar = true;
                    move self to vortexBag;
                    print "You put ", (the) self, " into the vortex bag.^";
                    return ItemFirstTaken();
                }
                if (second == captainsQuartersDesk) {
                    if (kabar in vortexBag)
                        "The ka-bar is a relic, and you wouldn't want to damage it. You're here to make as much as you can.";
                    move kabar to vortexBag;
                    print "The ka-bar is a relic, and you wouldn't want to damage it. So you put it in the vortex bag.^";
                    return ItemFirstTaken();
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Examine, Search:
                player.advanceGravity = false;
                if (self.spitOn) "This old military relic melts in the acid that's been sprayed all around.";
                "It's a relic, an old military Ka-Bar engraved with USMC. You've heard of the USCMC. The Colonial Marines are famous. But the USMC?";
            Kick:

            Take:
                if (self.spitOn) "It's been doused with acid. It's worthless.";
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                captainsQuarters.takenKaBar = true;
                move self to vortexBag;
                print "You take ", (the) self, ", putting it in the vortex bag.^";
                return ItemFirstTaken();
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            Rub, Pull, Push, PushDir, Turn:
                if (self.spitOn) "Doused with acid, you would burn yourself if you tried that.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        print "You can't quickly get to ", (the) self, ".";
                        return StandingDeath();
                    }
                }
            default:
                if (self.spitOn) "It's doused with acid. There's no need to do that.";
        ],
        spitOn false;
