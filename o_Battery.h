
! ---------------------------------------------------------------------------- !
!       BATTERY. 12/09/21
!

Object  battery "battery"
  with  name 'battery' 'plug' 'd-cell' 'cell' 'rechargeable',
        before [;
            Attack:
                "Are you really going to break the stuff you're trying to loot?";
            Burn:

            Drop:
                if (self in player || self in vortexBag) "You don't want to do that. It might come in handy.";
            Go:
                "You are already here.";
            ThrowAt:
                if (second == alien) {
                    if (self in musicBox || self in vortexBag) {
                        deadflag = 1;
                        "You can't quickly get to the battery.^^With you standing there doing nothing, the xenomorph jumps on top of you, throwing you to the ground. Its large claws keep you in place as a smiling mouth opens, the inner jaw going for your skull. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                    if (self in player) {
                        deadflag = 1;
                        "You throw the battery as hard as possible, but the creature bats it away. Then the xenomorph jumps, throwing you to the ground. Its large claws keep you in place as a smiling mouth opens, the inner jaw going for your skull. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                }
            Insert:
                if (self in vortexBag && second == vortexBag) "", (The) self, " is already here.";
                if (second == vortexBag) {
                    move self to vortexBag;
                    print "You put the battery into the vortex bag.^";
                    return ItemFirstTaken();
                }
                if (second == dataReader && self in player) {
                    "That doesn't fit in there, so you hold on to it.";
                }
                if (second == dataReader && self in vortexBag) {
                    "That doesn't fit in there, so you leave it in the bag.";
                }
                if (second == maintenanceGaragePanel) {
                    if (maintenanceGarageDoor.isDoorOpen) {
                        if (self in maintenanceGaragePanel) "The battery is already in the panel.";
                        "You don't need to reinsert it. The doors are already open.";
                    }
                    move self to maintenanceGaragePanel;
                    maintenanceGarageDoor.isDoorOpen = true;
                    iMonsterDestination = MAINTNNCGRGE;
                    "The doors are hotwired because the moment you insert the battery, machinery
                    kicks in, slowly grinding metal on metal as the doors begin to open. Once they
                    crack, more smoke pours into this room. The doors sound
                    like they could get stuck with gears that haven't been oiled in decades, but
                    they fully open, giving you access to the room in the back.";
                }
                if (second == computerRoomPanel) {
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
                "The battery is a square, rechargeable D-Cell.";
            Kick:

            Take:
                if (self in maintenanceGaragePanel) {
                    move self to player;
                    "You pop out the battery, expecting the doors to close. But they hold firm, the gears now jammed in place.";
                }
                if (self in player) "You already have that.";
                move self to player;
                if (self.alreadyTaken) "Taken.";
                self.alreadyTaken = true;
                print "You take the battery. Maybe this could be used for something else.^";
                return ItemFirstTaken();
            PutOn:
                if (self in player || self in vortexBag) {
                    if (second has supporter) "You don't want to leave that behind.";
                }
        ],
        alreadyTaken false;
