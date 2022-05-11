
! ---------------------------------------------------------------------------- !
!       STUN BATON. 11/18/21
!

Object  stunBaton "baton"
  with  name 'stun' 'baton' 'base' 'ring' 'rings' 'wand' 'device',
        describe [;
            if (weaponsLocker.takenBaton) rfalse;
            if (weaponsLocker.takenArmor == false) rtrue;
            if (self.spitOn) "^The pallet is covered in acid while a stun baton melts next to it.";
            if (weaponsLocker.takenBaton == false) "^Next to the pallet is a stun baton.";
            rtrue;
        ],
        before [;
            Attack:
                if (self.spitOn) "It melts in a pool of acid. There's no need to do that.";
                if (weaponsLocker.takenBaton == false) "That could be a useful weapon, and you're going to try and break it?";
                if (self.alreadyAttacked) "You hit your hand with the baton. It does nothing. It's been fully discharged.";
                "The baton is already working. You don't need to do that.";
            Burn:

            Drop:
                if (self.alreadyAttacked) {} else {
                    if (self in player) "You don't want to do that. It still has a charge left.";
                }
            Go:
                "You are already here.";
            Insert:
                if (self.spitOn) "There's is not much left. It has nearly melted away.";
                if (second == vortexBag) {
                    if (self in vortexBag) "", (The) self, " is already here.";
                    move self to vortexBag;
                    if (weaponsLocker.takenBaton) {
                        if (iCattleProdCharge > 0) {
                            if (cattleProd in player) {
                            } else {
                                move cattleProd to player;
                                "You put the baton into the vortex bag, pulling out the cattle prod. You need something to protect yourself.";
                            }
                        }
                    }
                    weaponsLocker.takenBaton = true;
                    "You put the baton into the vortex bag.";
                }
                if (second == aftCompanionwayDeckBLadder) {
                    if (self.alreadyAttacked == false) "That still works. You don't want to lose it.";
                    move self to aftCompanionwayDeckC;
                    iMonsterDestination = AFTCOMPDECKC;
                    print "You drop the stun baton into the ladder well";
                    if (iCattleProdCharge > 0) {
                        move cattleProd to player;
                        print ", taking the cattle prod to protect yourself";
                    }
                    print ". It clangs, reaching the bottom. But ";
                    "it's not loud, no bigger than the ship's creaking. You're not sure if the xenomorph heard it.";
                }
                if (second == forwardCompanionwayDeckALadder) {
                    if (self.alreadyAttacked == false) "That still works. You don't want to lose it.";
                    move self to forwardCompanionwayDeckC;
                    print "You drop the stun baton into the ladder well";
                    if (iCattleProdCharge > 0) {
                        move cattleProd to player;
                        print ", taking the cattle prod to protect yourself";
                    }
                    print ". It clangs, reaching the bottom. But ";
                    if (forwardStarboardJunctionDeckC.pipesBlown) "you fail to hear it hit the deck. The sound of venting gas from below is too loud.";
                    iMonsterDestination = FWDCOMPDECKC;
                    "it's not loud, no bigger than the ship's creaking. You're not sure if the xenomorph heard it.";
                }
                if (second == forwardCompanionwayDeckBLadder) {
                    if (self.alreadyAttacked == false) "That still works. You don't want to lose it.";
                    move self to forwardCompanionwayDeckC;
                    print "You drop the stun baton into the ladder well";
                    if (iCattleProdCharge > 0) {
                        move cattleProd to player;
                        print ", taking the cattle prod to protect yourself";
                    }
                    print ". It clangs, reaching the bottom. But ";
                    if (forwardStarboardJunctionDeckC.pipesBlown) "you fail to hear it hit the deck. The sound of venting gas from below is too loud.";
                    iMonsterDestination = FWDCOMPDECKC;
                    "it's not loud, no bigger than the ship's creaking. You're not sure if the xenomorph heard it.";
                }
                if (second == dataReader || second == musicBox || second == maintenanceGaragePanel || second == computerRoomPanel) {
                    "That doesn't fit in there.";
                }
                if (second == infirmaryCabinet || second == personalLockerRoomLocker) {
                    "That doesn't belong in there.";
                }
            Examine, Search:
                player.advanceGravity = false;
                if (self.spitOn) {
                    if (weaponsLocker.takenArmor == false) "The stun baton got hit by acid spewed all over the place. It now melts with the trooper armor, nearly dissolving away in the acidic secretions.";
                    "The stun baton got hit by acid spewed all over the place. It melts next to an industrial pallet, nearly dissolving away in the acidic secretions.";
                }
                print "The top of the stun baton has three rings that can deliver 50,000 volts when striking
                a subject. Intending to paralyze, not kill";
                if (self.alreadyAttacked) ". But the device has been fully discharged.";
                if (weaponsLocker.takenBaton == false) ". If you're are lucky, it still works.";
                ".";
            Kick:

            Swing:
                if (self.spitOn) "It melts in a pool of acid. You would burn yourself if you tried that.";
                if (parent(player) == parent(alien)) {
                    if (self.alreadyAttacked) {
                        deadflag = 1;
                        "You swing the baton one more time, hoping for it to trigger. But when it doesn't, the alien
                        swings at you - sending you into the bulkhead and breaking your ribs. When the alien's done, you
                        bleed out before the ship's crushed from the pressure of the sun.";
                    }
                    self.alreadyAttacked = true;
                    StopDaemon(alien);
                    remove alien;
                    player.alienHide = true;
                    player.alienMove = false;
                    if (self in vortexBag) print "You quickly pull the stun baton out of the vortex bag. ";
                    if (self in weaponsLocker) print "You quickly pick it up off the deck. ";
                    move self to parent(player);
                    print "With a short stab to the groin, the creature screams, choking on some acid. It swipes
                    at the baton, knocking it out of your hand, before jumping into the closest vent.^
                    ^The stun baton is worthless now";
                    if (iCattleProdCharge > 0) {
                        move cattleProd to player;
                        ", so you pick up the cattle prod to defend yourself.";
                    }
                    ".";
                }
                if (self in player) {
                    print "You swing the baton back and forth through the air";
                    if (self.alreadyAttacked == false) ". This might deter the creature.";
                    ".";
                }
            SwitchOn, SwitchOff:
                if (self.spitOn) "It melts in a pool of acid. You would burn yourself if you tried that.";
                "It doesn't work like that. You hit it once to turn it on. Then you have to discharge it.";
            Take:
                if (self.spitOn) "It has nearly melted away. It's worthless.";
                if (self.alreadyAttacked) {
                    if (self in player) "You already have that.";
                    if (self in vortexBag) {
                        move self to player;
                        "You take the stun baton. It might be useful.";
                    }
                    if (cattleProd in player) {
                        move self to vortexBag;
                        "The stun baton is spent, so you put it in the vortex bag.";
                    }
                }
                if (sledgehammer in player) {
                    move sledgehammer to vortexBag;
                    print "(first putting the sledgehammer in the bag)^";
                }
                if (cattleProd in player) {
                    move cattleProd to vortexBag;
                    print "(first putting the cattle prod in the bag)^";
                }
                if (weaponsLocker.takenBaton == false) {
                    weaponsLocker.takenBaton = true;
                    move self to player;
                    "You take the baton, hitting it once. The ring at the base lights up. This should at least give you another chance.";
                }
            PutOn:
                if (self in player || self in vortexBag) {
                    if (second has supporter) "You don't want to leave that behind.";
                    if (second == aftStarboardJunctionDeckCBattery || second == aftStarboardJunctionDeckCWelder) <<Tie self second>>;
                }
            Rub, Push, Pull, PushDir, Turn:
                if (self.spitOn) "There's is not much left. It has nearly melted away.";
            Touch:
                if (second == aftStarboardJunctionDeckCBattery || second == aftStarboardJunctionDeckCWelder) <<Tie self second>>;
            Tie:
                if (second == aftStarboardJunctionDeckCBattery || second == aftStarboardJunctionDeckCWelder) {
                    print "There's no way to tie the stun baton into the battery. ";
                    if (self.alreadyAttacked) "You can't charge it. It won't work again.";
                    "You have 1 charge. Nothing more.";
                }
            ThrowAt:
                if (self.spitOn) "There's is not much left. It has nearly melted away.";
                if (second == alien) {
                    if (self in vortexBag) {
                        deadflag = 1;
                        "You can't quickly get to the stun baton.^^The beast spits one more time before jumping, slamming into you while breaking your rib cage. The xenomorph begins to claw through flesh as you try to scream. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                    if (self in player) {
                        deadflag = 1;
                        if (self.alreadyAttacked) print "You hurl the stun baton, but it just bounces off the creature.";
                        else print "You hurl the stun baton, but it fails to trigger, bouncing off the creature.";
                        "^^The beast spits one more time before jumping, slamming into you while breaking your rib cage. The xenomorph begins to claw through flesh as you try to scream. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                }
                if (self in player) "That's not how you are suppose to use it.";
            default:
                if (self.spitOn) "It melts in a pool of acid. There's no need to do that.";
        ],
        alreadyAttacked false,
        spitOn false;
