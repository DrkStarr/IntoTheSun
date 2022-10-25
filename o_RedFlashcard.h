
! ---------------------------------------------------------------------------- !
!       ORANGE FLASHCARD. 11/08/21
!

Object  redFlashcard "orange flashcard"
  with  name 'orange' 'flash' 'card' 'flashcard' 'chip' 'thin',
        describe [;
            if (self in captainsQuarters) {
                if (captainsQuarters.alienWrecked) "^Next to the bed, among some scattered wood pieces, there's an orange flashcard.";
                "^Next to the bed, there's an orange flashcard.";
            }
            rtrue;
        ],
        before [;
            Attack:
                "This data on the card is valuable. You think twice about breaking it.";
            Burn:

            Drop:
                "The plastic might not be worth much, but the data is invaluable. You keep it.";
            Go:
                "You are already here.";
            Insert:
                return InsertRedCard();
            UseItem:
                if (self in player) {
                    return InsertRedCard();
                } else {
                    "You need to be holding the object before you can use it.";
                }
            Examine, Search:
                player.advanceGravity = false;
                print "The orange flashcard has the word ~Captain~ written along its side";
                if (self in player || self in vortexBag) ".";
                if (captainsQuarters.alienWrecked) ". Luckily it's not covered in any acid.";
                ".";
            Kick:

            Take:
                if (captainsQuarters.takenRedCard == false) {
                    captainsQuarters.takenRedCard = true;
                    move self to player;
                    "You take the flashcard, holding on to it for now.";
                }
                if (self in dataReader) dataReader.&name-->5 = 'ph017';
            Pull:
                <<Take self>>;
            PutOn:
                if (self in player || self in vortexBag) {
                    if (second has supporter) "You don't want to leave that behind.";
                }
            ThrowAt:
                if (second == alien) {
                    if (self in vortexBag) {
                        deadflag = 1;
                        "You can't quickly get to the orange flashcard.^^The xenomorph wastes no time making short work of you. Claws come at you, bones break, and then your screams. But it doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                    if (self in player) {
                        deadflag = 1;
                        "You throw the orange flashcard, but it bounces off the creature. Maybe it would've struck an eye if you got lucky, but no such luck.^^The xenomorph wastes no time making short work of you. Claws come at you, bones break, and then your screams. But it doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                }
        ];

  [ InsertRedCard;
        if (second == dataReader) {
            if (redFlashcard in dataReader) "The orange flashcard is already in the data reader.";
            if (dataReader in player) {
                move redFlashcard to dataReader;
                if (yellowFlashCard in dataReader) {
                    move yellowFlashCard to player;
                    print "(first removing the yellow flashcard)^";
                }
            } else {
                move dataReader to player;
                print "(first taking the data reader)^";
                move redFlashcard to dataReader;
                if (yellowFlashCard in dataReader) {
                    move yellowFlashCard to player;
                    print "(next removing the yellow flashcard)^";
                }
            }
            captainsQuarters.takenRedCard = true;
            dataReader.&name-->5 = 'information';
            "You insert the orange flashcard into the data reader. Immediately information pops up on the screen.";
        }
        if (second == vortexBag) {
            captainsQuarters.takenRedCard = true;
        }
        if (second == musicBox || second == maintenanceGaragePanel || second == computerRoomPanel) {
            "That doesn't properly fit in there.";
        }
        if (second == infirmaryCabinet || second == personalLockerRoomLocker) {
            "That doesn't belong in there.";
        }
        if (second == aftCompanionwayDeckBLadder || second == forwardCompanionwayDeckALadder || second == forwardCompanionwayDeckBLadder) {
            "You don't want to lose that.";
        }
        rfalse;
  ];
