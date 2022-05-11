
! ---------------------------------------------------------------------------- !
!       VORTEX BAG. 10/08/21
!

Object  vortexBag "vortex bag"
  with  name 'vortex' 'bag' 'pack' 'satchel' 'hole',
        before [;
            Attack:
                "In this situation, its value is immeasurable, and you would try to break it?";
            Burn:

            Insert:
                if (second == dataReader) "That doesn't fit in there.";
                if (second == musicBox || second == maintenanceGaragePanel || second == computerRoomPanel) {
                    "That doesn't fit in there.";
                }
                if (second == infirmaryCabinet || second == personalLockerRoomLocker) {
                    "That doesn't belong in there.";
                }
                "You better hold on to the vortex bag.";
            Go:
                "You are already here.";
            Examine:
                player.advanceGravity = false;
                "The vortex bag's slung over your shoulder. This amazing satchel is only obtainable through
                black markets from shady dealers. It reduces the mass of objects put inside it. As a result,
                everything gets smaller and lighter, allowing you to carry anything of value.";
            Empty:
                if (EmptyBag()) "Not here. Wait until you make landfall and you can sell all the goods.";
            Disrobe, Drop, Remove:
                "You think twice about that. It's the only way you're going to get the loot off the ship.";
            ThrowAt:
                if (second == alien) {
                    deadflag = 1;
                    "You throw the vortex bag, trying to distract the alien. But the creature hones in on you. Then it
                    jumps, hitting you with the full force of its body. With your wind knocked out, you can't scream as
                    the beast tears into your flesh. It doesn't take long before you bleed out, only to be crushed from
                    the pressure of the sun.";
                }
                if (self in player) "That's not how you are suppose to use it.";
            PutOn:
                if (second has supporter) "You don't want to leave that behind.";
            Open:
                if (EmptyBag()) "The vortex bag is already open. You can see the stuff inside.";
                "The vortex bag is already open. You can put stuff inside.";
            Close:
                "You don't need to do that. You need to loot the ship.";

        ],
   has  container open;
