
! ---------------------------------------------------------------------------- !
!       OUTFIT. 10/08/21
!
  Object  outfit
    with  name 'outfit' 'cloths' 'clothes' 'suit' 'bodysuit' 'mesh' 'thin' 'jeans' 'flannel' 'shirt' 'boots' 'polymer',
          short_name "your outfit",
          before [;
              Attack:
                  "You don't want to damage the polymer. It's protecting you from the atmosphere on this ship.";
              Disrobe, Remove:
                  "Thinking about streaking around here?";
              Give, ThrowAt:
                  "(first removing your clothes)^
                  Thinking about streaking around here?";
              Go:
                  "You are already here.";
              Examine, Search:
                  player.advanceGravity = false;
                  "A thin polymer bodysuit protects you so your skin is never exposed, sealing you
                  in and supplying you with oxygen. It's transparent and allows for unencumbered
                  movement. Your outfit? Nothing more than boots, jeans, and a flannel shirt.";
              Show:

              Take:

              Wear:

              Eat:

              PutOn:
                  if (second has supporter)
                      "(first removing your clothes)^
                      Thinking about streaking around here?";
          ],
    has   proper clothing worn container open;
