
! ---------------------------------------------------------------------------- !
!       CATTLE PROD. 10/08/21
!

Object  cattleProd "cattle prod"
  with  name 'cattle' 'prod' 'rod' 'pole' 'object' 'spikes' 'electric' 'end' 'power' 'indicator' 'handle' 'grip' 'primitive' 'weapon',
        describe [;
            if (self.isHidden) rtrue;
            rfalse;
        ],
        before [;
            Attack:
                if (iCattleProdCharge == 0) rfalse;
                if (alien.sleeping) "This weapon is invaluable, and you're going to break it? You have no idea what's on this ship.";
                "This weapon is invaluable. You think twice about breaking it.";
            Drop:
                if (iCattleProdCharge == 0) {
                    self.isHidden = false;
                    rfalse;
                }
                if (self in player) "You don't want to do that. You're going to need it.";
            Burn:

            Swing:
                if (self in player) {
                    if (parent(player) == parent(alien)) <<Attack alien>>;
                    if (iCattleProdCharge == 0)
                        "You swing it back and forth, cutting the air. But it's out of power, and if you hit something, it would break the rod.";
                    "You swing the rod back and forth, cutting the air. If this rod hit someone, they would feel it.";
                }
                "You are not holding that.";
            UseItem:
                if (self in player) {
                    if (second == alien) <<Attack alien>>;
                    if (second == player) "Hitting yourself with that would make you piss uncontrollably.";
                    if (second == forwardCorridorDeckBBody) <<Attack forwardCorridorDeckBBody self>>;
                    if (second == pod) <<Prod pod>>;
                    if (second == forwardPortJunctionDeckBDust) <<Attack forwardPortJunctionDeckBDust>>;
                    return InsertCattleProd();
                } else {
                    "You need to be holding the object before you can use it.";
                }
            Go:
                "You are already here.";
            Insert:
                return InsertCattleProd();
            Examine, Search:
                player.advanceGravity = false;
                print "The pole is a meter in length with electric spikes at the end. Looking at the grip, ";
                if (iCattleProdCharge == 3) "there are three out of five bars lit on the power indicator.";
                if (iCattleProdCharge == 2) "there are two out of five bars lit on the power indicator.";
                if (iCattleProdCharge == 1) "there is one out of five bars lit on the power indicator.";
                "the power indicator's not lit at all. There's no juice in it. You need to get off the ship before the alien kills you.";
            Kick:

            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        deadflag = 1;
                        "You can't quickly get to the cattle prod.^^Standing there doing nothing, the xenomorph swings at you, connecting with your ribs. You scream. It slashes, cutting you across the face. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                    if (self in player) {
                        deadflag = 1;
                        "That's not how you are suppose to use it.^^Standing there doing nothing, the xenomorph swings at you, connecting with your ribs. You scream. It slashes, cutting you across the face. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                }
                if (self in player) "That's not how you are suppose to use it.";
            Touch:
                if (second == aftStarboardJunctionDeckCBattery || second == aftStarboardJunctionDeckCWelder || second == aftCompanionwayDeckCBattery) <<Tie self second>>;
                if (self in player) "Touching the end would make you piss yourself.";
                self.taken = false;
                move self to player;
                "Careful not to take it by the wrong end, you pick up the rod. What did this guy encounter?";
            Rub:
                "The cattle prod is as clean as it's going to get.";
            SwitchOn:
                if (iCattleProdCharge < 1) "It doesn't work like that. The pole is out of power.";
                "It doesn't work like that. But the pole is charged and will shock whatever it touches.";
            SwitchOff:
                "It doesn't work like that. Instead, it's hotwired and will work until it runs out of power.";
            Take:
                if (self.taken) {
                    self.taken = false;
                    move self to player;
                    "You pick up the cattle prod - what did this guy encounter?";
                }
                if (sledgehammer in player) {
                    move sledgehammer to vortexBag;
                    print "(first putting the sledgehammer in the bag)^";
                }
                if (stunBaton in player) {
                    move stunBaton to vortexBag;
                    print "(first putting the baton in the bag)^";
                }
            PutOn:
                if (self in player || self in vortexBag) {
                    if (second has supporter) "You don't want to leave that behind.";
                    if (second == aftStarboardJunctionDeckCBattery || second == aftStarboardJunctionDeckCWelder || second == aftCompanionwayDeckCBattery || second == foodLockerCorridorDeckBSensor) <<Tie self second>>;
                }
            Tie:
                if (second == aftStarboardJunctionDeckCBattery || second == aftStarboardJunctionDeckCWelder || second == aftCompanionwayDeckCBattery) {
                    print "There's no way to tie the cattle prod into the battery. ";
                    if (iCattleProdCharge == 0) "And you can't charge it. It won't work again.";
                    print "You have ";
                    if (iCattleProdCharge == 3) print "3 charges";
                    if (iCattleProdCharge == 2) print "2 charges";
                    if (iCattleProdCharge == 1) print "1 charge";
                    ". Nothing more.";
                }
                if (second == foodLockerCorridorDeckBSensor) "The relay isn't a battery. It runs off the ship's power when in use.";
            Push, PushDir, Pull:
                if (self in forwardCorridorDeckB) "You don't need to do that, but you might want to take it.";

        ],
        taken true,
        isHidden true,
        firstTime true;

  [ InsertCattleProd;
        if (second == vortexBag) {
            if (cattleProd in vortexBag) "", (The) cattleProd, " is already here.";
            if (sledgehammer in vortexBag) {
                move sledgehammer to player;
                move cattleProd to vortexBag;
                "You put the cattle prod into the vortex bag, pulling out the sledgehammer. You need something to protect yourself.";
            }
            "You don't want to do that. How could you defend yourself?";
        }
        if (second == dataReader) {
            "That doesn't fit in there.";
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
        rfalse;
  ];
