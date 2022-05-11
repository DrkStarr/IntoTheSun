
! ---------------------------------------------------------------------------- !
!       LAPTOP. 11/06/21
!

Object  laptop "laptop"
  with  name 'laptop' 'conflictcomputer' 'dust' 'ph002'  'ph003' 'ph014' 'ph015' 'ph016',
        describe [;
            rtrue;
        ],
        before [;
            Attack:
                if (self.spitOn) "Sitting in a pool of the alien's secretions, hitting the laptop would splash acid all over the place. Covering your body and melting your flesh.";
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
                if (self.spitOn) "You would burn yourself. It's sitting in a pool of acid.";
                if (second == dataReader) {
                    if (controlRoomDeckC.takenLaptop) {
                        "That doesn't fit in there.";
                    } else {
                        move self to vortexBag;
                        controlRoomDeckC.takenLaptop = true;
                        print "That doesn't fit in there, so you move it to the vortex bag.^";
                        return ItemFirstTaken();
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    controlRoomDeckC.takenLaptop = true;
                    move self to vortexBag;
                    print "You put ", (the) self, " into the vortex bag.^";
                    return ItemFirstTaken();
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Examine, Search:
                player.advanceGravity = false;
                if (self.spitOn) "Internal circuitry dissolves while the cables from the engineering panel melt - the whole thing now a pool of sludge.";
                if (controlRoomDeckC.takenLaptop) "The laptop is old, covered in dust and surely not working. It's an antique at best.";
                "The laptop is old, covered in dust and plugged into a number of strange cables that coil out of the engineering panel.";
            Kick:

            Take, Remove, Turn, Pull:
                if (self.spitOn) "The electronics are destroyed. It's worthless.";
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                controlRoomDeckC.takenLaptop = true;
                move self to vortexBag;
                print "You unplug the laptop from all the wires running out of it, putting it in the vortex bag.^";
                return ItemFirstTaken();
            Push, Pull, PushDir, Turn:
                if (self.spitOn) "You would burn yourself. It's sitting in a pool of acid.";
                if (self in vortexBag) "It's in the bag. You don't need to do that.";
                "What do you want to do? Push it off the bench? You would damage it.";
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            Rub:
                if (self.spitOn) "You would burn yourself. It's sitting in a pool of acid.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        print "You can't quickly get to ", (the) self, ".";
                        return StandingDeath();
                    }
                }
            default:
                if (self.spitOn) "It's sitting in a pool of acid. There's no need to do that.";
        ],
        spitOn false;
