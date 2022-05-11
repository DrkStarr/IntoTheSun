
! ---------------------------------------------------------------------------- !
!       TROOPER ARMOR. 11/18/21
!

Object  trooperArmor "trooper armor"
  with  name 'trooper' 'armor' 'container',
        describe [;
            if (self.spitOn) {
                if (weaponsLocker.takenBaton == false) "^On the pallet is a set of trooper armor covered in acid. A stun baton melts along with it.";
                "^On the pallet is a set of trooper armor covered in acid that's been sprayed across the room.";
            }
            if (weaponsLocker.takenArmor == false) {
                print "^On the pallet is a set of trooper armor";
                if (weaponsLocker.takenBaton == false) print ". Next to it a stun baton";
                ".";
            }
            rtrue;
        ],
        before [;
            Attack:
                if (self.spitOn) "Laying in acid, hitting that would kick up the vomit, burning through your flesh as it devours your organs.";
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
                if (self.spitOn) "You'd only burn yourself. It's covered in acid.";
                if (second == dataReader) {
                    if (weaponsLocker.takenArmor) {
                        "That doesn't fit in there.";
                    } else {
                        move self to vortexBag;
                        weaponsLocker.takenArmor = true;
                        "That doesn't fit in there, so you move it to the vortex bag.";
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    weaponsLocker.takenArmor = true;
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Examine, Search:
                player.advanceGravity = false;
                if (self.spitOn) "A vile liquid was vomited all over the place, covering the pallet and everything else. Acid boils through military-grade armor.";
                "Packed in a container, this military-grade armor has been used by the USCMC for over a hundred years. As old as it is, it still has value.";
            Kick:

            Open:
                if (self.spitOn) "You'd only burn yourself. It's covered in acid.";
                "You should leave it sealed. You'll get more money for it.";
            Close:
                if (self.spitOn) "You'd only burn yourself. It's covered in acid.";
                "The container is already closed.";
            Take:
                if (self.spitOn) "It's covered in acid. It's worthless.";
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                if (weaponsLocker.takenArmor == false) {
                    weaponsLocker.takenArmor = true;
                    move self to vortexBag;
                    "You take the armor. It's heavy to pick up but light once it enters the bag.";
                }
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            Wear:
                if (self.spitOn) "You'd only burn yourself. It's covered in acid.";
                "An old set of armor like that wouldn't protect you, not from the xenomorph onboard. Its acid can burn through metal, and its large claws can crush bones. Plus, the armor is worth more sealed in its container if you get it off the ship.";
            Rub, Push, Pull, PushDir, Turn:
                if (self.spitOn) "You'd only burn yourself. It's covered in acid.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        print "You can't quickly get to ", (the) self, ".";
                        return StandingDeath();
                    }
                }
            default:
                if (self.spitOn) "It melts in a pool of acid. There's no need to do that.";
        ],
        spitOn false,
   has  proper;
