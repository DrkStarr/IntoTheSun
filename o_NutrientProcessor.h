
! ---------------------------------------------------------------------------- !
!       NUTRIENT PROCESSOR. 01/06/22
!

Object  nutrientProcessor "nutrient processor"
  with  name 'nutrient' 'processor' 'bulky' 'unit',
        describe [;
            if (self in galley) {
                "^Along the port bulkhead, a nutrient processor sits in the corner of this room.";
            }
            rtrue;
        ],
        before [;
            Attack:
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
                if (second == dataReader) {
                    if (galley.takenProcessor) {
                        "That doesn't fit in the reader. You leave ", (the) self, " in the vortex bag.";
                    } else {
                        galley.takenProcessor = true;
                        move self to vortexBag;
                        print "(first taking picking up ", (the) self, ")^";
                        print "That doesn't fit in the reader, so you move it to the vortex bag.^";
                        return ItemFirstTaken();
                    }
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    if (self in vortexBag) "You don't want to lose that, so you keep it in the bag.";
                }
                if (second == vortexBag) {
                    galley.takenProcessor = true;
                    move self to vortexBag;
                    print "It's big and bulky, but you take the nutrient processor cramming it in the hole as the bag pulls it into the vortex.^";
                    return ItemFirstTaken();
                }
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (self in vortexBag) {
                    "You don't want to leave it behind, so you keep it in the bag.";
                }
            Examine, Search:
                player.advanceGravity = false;
                print "The nutrient processor is a bulky unit that converts organic material into edible food paste";
                if (galley.takenProcessor) ".";
                ". Not the most appetizing, but it keeps the crew alive.";
            Take:
                if (self in vortexBag) "You don't need that. You'll be able to sell it later.";
                galley.takenProcessor = true;
                move self to vortexBag;
                print "It's big and bulky, but you take the nutrient processor cramming it in the hole as the bag pulls it into the vortex.^";
                return ItemFirstTaken();
            PutOn:
                if (self in vortexBag && second has supporter) "You don't want to leave that behind. You'll be able to sell it later once you get off the ship.";
            Push, Pull, PushDir, Turn:
                if (self in vortexBag) "That's not going anywhere. It's in the vortex bag.";
                "It's big and bulky and hard to move around, but it would fit into your bag.";
            Rub:

            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        print "You can't quickly get to ", (the) self, ".";
                        return StandingDeath();
                    }
                }
        ];
