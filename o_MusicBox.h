
! ---------------------------------------------------------------------------- !
!       MUSIC BOX. 12/09/21
!

Object  musicBox "music box"
  with  name 'music' 'box' 'access' 'plate' 'simple' 'switch' 'device',
        invent [;
            if (self.openedFirstTime == false) {
                print "a music box";
                rtrue;
            }
        ],
        before [;
            Attack:
                if (self.spitOn) "You don't want to hit that. It's melting in a pool of acid. It would splash back at you, melting off your face.";
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
                if (self.spitOn) "You don't want to touch that. It's melting in a pool of acid.";
                if (second == dataReader) {
                    if (crewLounge.takenMusicBox) {
                        "That doesn't fit in there.";
                    } else {
                        move self to vortexBag;
                        crewLounge.takenMusicBox = true;
                        print "That doesn't fit in there, so you move it to the vortex bag.^";
                        return ItemFirstTaken();
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    crewLounge.takenMusicBox = true;
                    move self to vortexBag;
                    print "You put ", (the) self, " into the vortex bag.^";
                    return ItemFirstTaken();
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Examine:
                player.advanceGravity = false;
                if (self.spitOn) "The music box got blasted pretty good when the alien spit on the hovering disk. The box melts in a pool of acid along with the table.";
                print "The music box is nothing more than a set of speakers with a switch on the side to operate it. ";
                if (self has open) {
                    if (battery in self) "The access plate is open, and there's a battery inside.";
                    "On the back of it, the access plate is open.";
                }
                "It has an access plate on the back of it.";
            Kick:

            Take:
                if (self.spitOn) "It's melting in a pool of acid. It's worthless.";
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                crewLounge.takenMusicBox = true;
                move self to vortexBag;
                print "You take ", (the) self, ", putting it in the vortex bag.^";
                return ItemFirstTaken();
            Pull, PushDir, Turn:
                if (self.spitOn) "It's melting in a pool of acid. It's worthless.";
                if (self in vortexBag) "It's in the bag. You don't need to do that.";
                "You don't need to do that. You should take it. It might be worth something.";
            PutOn:
                if (self.spitOn) "You don't want to touch that. It's melting in a pool of acid.";
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            SwitchOn, Push, Turn:
                if (self.spitOn) "You don't want to touch that. It's melting in a pool of acid.";
                if (DistanceToAlien() > 0) {
                    if (alien.hitFirstTime) "The alien is close. You don't want to do that.";
                    "Something is close. You don't want to do that.";
                }
                if (self.listenedOnce) "You know it already works. There's no need to do that.";
                if (battery in self) {
                    self.listenedOnce = true;
                    "The soft music of Mozart begins to play in the room, but you quickly turn it off. This is no time to relax.";
                }
                "The device is silent, but the battery has been removed.";
            SwitchOff:
                "That's already off.";
            Open:
                if (self.spitOn) "You don't want to touch that. It's melting in a pool of acid.";
                self.openedFirstTime = true;
            Rub:
                if (self.spitOn) "You don't want to touch that. It's melting in a pool of acid.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        print "You can't quickly get to ", (the) self, ".";
                        return StandingDeath();
                    }
                }
            default:
                if (self.spitOn) "It's melting in a pool of acid. There's no need to do that.";
        ],
        spitOn false,
        listenedOnce false,
        openedFirstTime false,
   has  container openable ~open;
