
! ---------------------------------------------------------------------------- !
!       POD. 12/02/21
!

Object  pod "pod"
  with  name 'pod' 'oval' 'round' 'egg' 'large' 'seam' 'seams' 'husk' 'dry' 'brittle' 'fragile',
        describe [;
            "^In the middle of this corridor sits a large oval pod.";
        ],
        before [;
            Attack:
                if (self.touchedAlready)
                    "The pod's not a threat. It's not even alive.";
                move forwardPortJunctionDeckBDust to forwardPortJunctionDeckB;
                remove self;
                "You reach out, hitting the pod, not knowing what to expect. Your hand goes right through as
                it crumbles to dust. Whatever was inside died a long time ago.";
            Burn:

            Eat:
                "That would be less than appetizing.";
            Drink:
                "It's a dry husk. There's nothing to drink.";
            Close:
                "The pod's not open.";
            Climb:
                "It wouldn't support your weight. It's brittle as is.";
            Drop:

            Dig:
                "The pod is a dry, brittle husk. You'd break it if you tried that.";
            Go:
                "You are already here.";
            Insert:

            Examine, Search:
                player.advanceGravity = false;
                if (self.touchedAlready)
                    "The pod has to be old. The husk is dry and brittle. It was too easy to break.";
                "It's hard to see in all this smoke, but it's an organic pod with seams that criss-cross the top.";
            Kick:

            LookUnder:
                if (self.touchedAlready) "You'd have to move it, but the pod's too fragile to push.";
                "You'd have to move it, but the pod looks like it's stuck to the deck.";
            Take:
                if (self.touchedAlready) "The pod is dry, brittle, and not worth a thing.";
                "A sizeable organic pod like that would not be worth much and could cause many problems with customs.";
            Touch, Push, Pull, PushDir, Turn, Open, Unlock:
                if (self.touchedAlready)
                    "You don't want to damage the pod anymore. It's brittle.";
                self.touchedAlready = true;
                "You reach out, touching the pod, not knowing what to expect.
                It doesn't react. So you push a little harder. But because the husk is
                so dry, your fingers break through the surface. Instinctively, you pull
                back your hand.";
        ],
        brokenPod false,
        touchedAlready false,
   has  static;
