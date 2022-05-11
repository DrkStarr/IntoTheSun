
! ---------------------------------------------------------------------------- !
!       YELLOW FLASHCARD. 11/06/21
!

Object  yellowFlashcard "yellow flashcard"
  with  name 'yellow' 'flash' 'card' 'flashcard' 'chip' 'thin',
        describe [;
            if (self in maintenanceGarage) "^Lying in front of the broken workbench is a yellow flashcard.";
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
                if (second == dataReader) {
                    if (self in dataReader) "The yellow flashcard is already in the data reader.";
                    if (dataReader in player) {
                        move self to dataReader;
                        if (redFlashcard in dataReader) {
                            move redFlashcard to player;
                            print "(first removing the orange flashcard)^";
                        }
                    } else {
                        move dataReader to player;
                        print "(first taking the data reader)^";
                        move self to dataReader;
                        if (redFlashcard in dataReader) {
                            move redFlashcard to player;
                            print "(next removing the orange flashcard)^";
                        }
                    }
                    self.takenYellowcard = true;
                    dataReader.&name-->5 = 'information';
                    "You insert the yellow flashcard into the data reader. Immediately information pops up on the screen.";
                }
                if (second == vortexBag) {
                    self.takenYellowcard = true;
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
            Examine, Search:
                player.advanceGravity = false;
                "The yellow flashcard has the word ~Engineering~ written along the side of it.";
            Kick:

            Take:
                if (self.takenYellowcard == false) {
                    self.takenYellowcard = true;
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
                        "You can't quickly get to the yellow flashcard.^^The xenomorph spits, hitting you right in the face. You'd scream if you had a mouth, but you can only stagger for a moment before the beast slams into you, tearing apart your flesh. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                    if (self in player) {
                        deadflag = 1;
                        "You throw the yellow flashcard, but it bounces off the creature. Maybe it would've struck an eye if you got lucky, but no such luck.^^The xenomorph spits, hitting you right in the face. You'd scream if you had a mouth, but you can only stagger for a moment before the beast slams into you, tearing apart your flesh. It doesn't take long before you bleed out, only to be crushed from the pressure of the sun.";
                    }
                }
        ],
        takenYellowcard false;
