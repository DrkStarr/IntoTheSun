
! ---------------------------------------------------------------------------- !
!       SLEDGEHAMMER. 11/01/21
!

Object  sledgehammer "sledgehammer"
  with  name 'sledge' 'hammer' 'sledgehammer',
        describe [;
            rtrue;
        ],
        before [;
            Attack:
                "This tool is invaluable. You think twice about breaking it.";
            Drop:
                "You don't want to do that. You're going to need it.";
            Burn:

            Swing:
                if (parent(player) == parent(alien)) {
                    if (self.alreadyAttacked) {
                        if (second == cattleProd) {
                        } else {
                            print "A slow attack like that would miss the alien a second time";
                            if (iCattleProdCharge == 0) {
                                print ". ";
                            } else {
                                print ".^^";
                            }
                        }
                        if (iCattleProdCharge == 0) {
                            ! What If The Player Has The Baton? I don't care. Player still dies.
                            if (cattleProd in vortexBag || cattleProd in player) {
                                deadflag = 1;
                                "You drop the hammer, grabbing the cattle prod and rolling to one side. Then you try to stick
                                the alien with the rod, but nothing happens. You realize all too late that the rod is out
                                of power. When the alien's done, you bleed out before the ship's crushed from the pressure of
                                the sun.";
                            }
                        }
                        iCattleProdCharge--;
                        move self to vortexBag;
                        move cattleProd to player;
                        StopDaemon(alien);
                        remove alien;
                        player.alienHide = true;
                        player.alienMove = false;
                        if (self.hammerAlreadyUsed == false) {
                            self.hammerAlreadyUsed = true;
                            print "You drop the hammer, grabbing the cattle prod and rolling to one side. Turning, you stick the
                            alien with the rod as hard as you can. The creature screams and hisses, but you push the rod harder
                            into its chest. Swinging its arm, it knocks the rod out of your hand before spitting at you and then
                            jumping into the ventilation system";
                        } else {
                            self.hammerAlreadyUsed = false;
                            print "You drop the hammer, grabbing the cattle prod a second time. The alien tries to anticipate your
                            movement, but you swing the rod instead of rolling to one side. The creature fails to get out of the
                            way and cries out in pain. Hissing, it tries to spit on you. Then it jumps for the ventilation system
                            as it knocks the pole out of your hand again";
                        }
                        if (iCattleProdCharge == 0) ".^^Picking up the rod, you look at the handle. You're out of juice.";
                        ".^^After its gone, you pick up the cattle prod.";
                    }
                    self.alreadyAttacked = true;
                    StopDaemon(alien);
                    remove alien;
                    player.alienHide = true;
                    player.alienMove = false;
                    "You swing the hammer for all it's worth, connecting with the skull of the xenomorph. It cries
                    out in high-pitched pain before jumping up into the ventilation system, getting away from you.^
                    ^You got away with it this time, but the alien is intelligent and won't let a slow attack like
                    that through again.";
                }
                if (self in player) "You swing the hammer back and forth like a club through the air. It should do some damage.";
            Go:
                "You are already here.";
            Insert:
                if (second == vortexBag) {
                    if (self in vortexBag) "", (The) self, " is already here.";
                    if (maintenanceGarage.takenHammer) {
                        move cattleProd to player;
                        move self to vortexBag;
                        "You put the sledgehammer into the vortex bag, taking out the cattle prod. You need to stay protected.";
                    } else {
                        move cattleProd to player;
                        move self to vortexBag;
                        maintenanceGarage.takenHammer = true;
                        print "You put the sledgehammer into the vortex bag.^";
                        return ItemFirstTaken();
                    }
                }
                if (second == dataReader) {
                    if (maintenanceGarage.takenHammer) {
                        "That doesn't fit in there.";
                    } else {
                        move self to vortexBag;
                        maintenanceGarage.takenHammer = true;
                        print "That doesn't fit in there, so you move it to the vortex bag.^";
                        return ItemFirstTaken();
                    }
                }
                if (second == musicBox || second == maintenanceGaragePanel || second == computerRoomPanel) {
                    "That doesn't fit in there.";
                }
                if (second == infirmaryCabinet || second == personalLockerRoomLocker) {
                    "That doesn't belong in there.";
                }
                if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
                    "You don't want to lose that.";
                }
            Examine, Search:
                player.advanceGravity = false;
                if (self.alreadyAttacked) "It's a sledgehammer that makes for a slow attack. Now you're pushing it if you think you can use it as a weapon.";
                if (self in player || self in vortexBag) {
                    print "It's a sledgehammer. Slow, but the weight on the end might make for a good weapon";
                    if (alien.hitFirstTime) ". But the alien's quick, so who knows how really good it is.";
                    ".";
                }
                if (maintenanceGarage.alienWrecked) print "The hammer lies on the deck. It ";
                else print "Leaning against the garage door, the hammer ";
                "was probably used as a last resort when working on this equipment. Probably.";
            Kick:

            Push, Pull, PushDir:
                if (self in player || self in vortexBag) rfalse;
                "There's no reason to knock it over.";
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        deadflag = 1;
                        "You can't quickly get to the sledgehammer.^^Standing there doing nothing, the xenomorph closes the distance, jumping off, slamming into you. You cry out. It slashes, cutting you in half. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                    if (self in player) {
                        deadflag = 1;
                        "That's not how you are suppose to use it.^^Standing there doing nothing, the xenomorph closes the distance, jumping off, slamming into you. You cry out. It slashes, cutting you in half. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                }
                if (self in player) "That's not how you are suppose to use it.";
            Take:
                if (self in player) "You already have that.";
                if (cattleProd in player) {
                    move cattleProd to vortexBag;
                    print "(first putting the cattle prod in the bag)^";
                }
                if (stunBaton in player) {
                    move stunBaton to vortexBag;
                    print "(first putting the baton in the bag)^";
                }
                if (self in vortexBag) {
                    move self to player;
                    if (self.alreadyAttacked) "You pull out the sledgehammer from the vortex bag, but you're not going to be able to defend yourself with it.";
                    "You pull out the sledgehammer from the vortex bag, hoping that you'll still be able to defend yourself.";
                }
                move self to player;
                maintenanceGarage.takenHammer = true;
                print "You pick up the sledgehammer, hoping that you'll still be able to defend yourself.^";
                return ItemFirstTaken();
            PutOn:
                if (self in player || self in vortexBag) {
                    if (second has supporter) "You don't want to leave that behind.";
                }
        ],
        taken true,
        alreadyAttacked false,
        hammerAlreadyUsed false,
        cleaned false;
