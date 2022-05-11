
! ---------------------------------------------------------------------------- !
!       WINE. 12/07/21
!

Object  wine "rare wine"
  with  name 'rare' 'wine' 'case' 'label' 'labeling',
        describe [;
            if (self in foodStorage) {
                if (self.spitOn) "^A case of wine melts in a pool of acid, mixing the red liquid with the alien's secretions.";
                "^A case of rare wine peeks out from behind a few crates of prefab meals.";
            }
            rtrue;
        ],
        before [;
            Attack:
                if (self.spitOn) "Even though the wine mixes with the acid, hitting it would cause it to splash up into your chest, boring a hole through you.";
                "Are you really going to break the stuff you're trying to loot?";
            Burn:

            Drop:
                if (self in vortexBag) {
                    print "(first taking ", (the) self, " from the vortex bag)^";
                    "You should leave it in the vortex bag. You'll be able to sell it later.";
                }
            Drink:
                if (self.spitOn) "You can't drink that. It's sitting in a pool of acid.";
                "While you hope that it has aged well, you hold back. Who knows what it's worth.";
            Go:
                "You are already here.";
            Insert:
                if (self.spitOn) "You don't want to touch that. It's sitting in a pool of acid.";
                if (second == dataReader) {
                    if (foodStorage.takenWine) {
                        "That doesn't fit in the reader. You leave ", (the) self, " in the vortex bag.";
                    } else {
                        foodStorage.takenWine = true;
                        move self to vortexBag;
                        print "(first taking picking up ", (the) self, ")^";
                        "That doesn't fit in the reader, so you move it to the vortex bag.";
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You'd break it if you did that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    foodStorage.takenWine = true;
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Examine, Search:
                player.advanceGravity = false;
                if (self.spitOn) "The rare case already melted halfway through sitting in the pool of acid, draining the bottles of wine. They're worthless now and can't even be carried easily.";
                "The wine is from Italy and might be worth something if you can get it off this tug in one piece. The labeling all over the case is in Italian.";
            Read:
                if (self.spitOn) "It's too hard to read now. Acid damaged the writing.";
                "You don't need to figure out what it says.";
            Take:
                if (self.spitOn) "It's sitting in a pool of acid. It's worthless.";
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                foodStorage.takenWine = true;
                move self to vortexBag;
                print "You take ", (the) self, ", putting it in the vortex bag.^";
                return ItemFirstTaken();
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            Rub, Push, Pull, PushDir, Turn:
                if (self.spitOn) "You don't want to touch that. It's sitting in a pool of acid.";
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
