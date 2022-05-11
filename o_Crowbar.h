
! ---------------------------------------------------------------------------- !
!       CROWBAR. 11/06/21
!

Object  crowbar "crowbar"
  with  name 'crowbar' 'bar',
        describe [;
            if (self in controlRoomDeckC) "^On the ground in front of the cabinet is a crowbar.";
            rfalse;
        ],
        before [;
            Attack:
                "Made of thick metal, you're not going to be able to break the crowbar.";
            Burn:

            Drop:
                if (self in player) "You don't want to leave it behind, so you hold on to it.";
                if (self in vortexBag) "You don't want to leave it behind, so you keep it in the bag.";
            Go:
                "You are already here.";
            Insert:
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (second == vortexBag) {
                    move self to vortexBag;
                    "You put the crowbar into the vortex bag.";
                }
                if (second == dataReader && self in player) {
                    "That doesn't fit in there, so you hold on to it.";
                }
                if (second == dataReader && self in vortexBag) {
                    "That doesn't fit in there, so you leave it in the bag.";
                }
                if (second == musicBox || second == maintenanceGaragePanel || second == computerRoomPanel) {
                    "That doesn't fit in there.";
                }
                if (second == infirmaryCabinet || second == personalLockerRoomLocker) {
                    "That doesn't belong in there.";
                }
                if (second == aftCompanionwayDeckBLadder) {
                    move self to aftCompanionwayDeckC;
                    iMonsterDestination = AFTCOMPDECKC;
                    "You drop the crowbar into the ladder well. Then, with a sharp clang, it reaches the bottom.
                    That should attract the xenomorph to the lower part of the ship.";
                }
                if (second == forwardCompanionwayDeckALadder) {
                    move self to forwardCompanionwayDeckC;
                    print "You drop the crowbar into the ladder well";
                    if (forwardStarboardJunctionDeckC.pipesBlown) ", but fail to hear it crash into the deck. The sound of venting gas from below is too loud.";
                    iMonsterDestination = FWDCOMPDECKC;
                    ". Then, with a sharp clang, it reaches the bottom. That should attract the xenomorph to the lowest parts of the ship.";
                }
                if (second == forwardCompanionwayDeckBLadder) {
                    move self to forwardCompanionwayDeckC;
                    print "You drop the crowbar into the ladder well";
                    if (forwardStarboardJunctionDeckC.pipesBlown) ", but fail to hear it crash into the deck. The sound of venting gas from below is too loud.";
                    iMonsterDestination = FWDCOMPDECKC;
                    ". Then, with a sharp clang, it reaches the bottom. That should attract the xenomorph to the lower part of the ship.";
                }
            Examine, Search:
                player.advanceGravity = false;
                "The crowbar is nothing more than a simple piece of metal used to pry things open.";
            Kick:

            Take:
                if (self in player) "You already have that.";
                move self to player;
                if (self.alreadyTaken) "Taken.";
                self.alreadyTaken = true;
                "You take the crowbar, thinking you should have brought one on board.";
            PutOn:
                if (self in player || self in vortexBag) {
                    if (second has supporter) "You don't want to leave that behind.";
                }
            Swing:
                if (parent(player) == parent(alien)) {
                    deadflag = 1;
                    "You swing the crowbar at the alien, but it bats it away, breaking your arm. Then
                    the creature hits you in the chest, sending you flying back into the bulkhead and
                    breaking your ribs. When the alien's done, you bleed out before the ship's crushed
                    from the pressure of the sun.";
                }
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        deadflag = 1;
                        "You can't quickly get to the crowbar.^^A growl from inside the beast grows before it jumps straight at you, tackling you to the deck. Then the claws come down, tearing into flesh. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                    if (self in player) {
                        deadflag = 1;
                        "You hurl the crowbar, but it just bounces off the creature.^^A growl from inside the beast grows before it jumps straight at you, tackling you to the deck. Then the claws come down, tearing into flesh. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                }
        ],
        alreadyTaken false;
