! ==============================================================================
!   GRAMMAR:  Grammar table entries for the standard verbs library.
!
!   Supplied for use with Inform 6 -- Release 6.12.5 -- Serial number 210605
!
!   Copyright Graham Nelson 1993-2004 and David Griffith 2012-2021
!   This code is licensed under either the traditional Inform license as
!   described by the DM4 or the Artistic License version 2.0.  See the
!   file COPYING in the distribution archive or at
!   https://gitlab.com/DavidGriffith/inform6lib/
!
!   In your game file, Include three library files in this order:
!       Include "Parser";
!       Include "VerbLib";
!       Include "Grammar";
! ==============================================================================

System_file;

#Ifdef		LIBRARY_STAGE;
#Iffalse	LIBRARY_STAGE >= AFTER_GRAMMAR;	! if not already included
#Iftrue		LIBRARY_STAGE == AFTER_VERBLIB;	! if okay to include it

! ------------------------------------------------------------------------------
!  The "meta-verbs", commands to the game rather than in the game, come first:
! ------------------------------------------------------------------------------

Verb meta 'brief'
    *                                           -> LMode1;

Verb meta 'verbose' 'long'
    *                                           -> LMode2;

Verb meta 'superbrief' 'short'
    *                                           -> LMode3;

Verb meta 'normal'
    *                                           -> LModeNormal;

Verb meta 'notify'
    *                                           -> NotifyOn
    * 'on'                                      -> NotifyOn
    * 'off'                                     -> NotifyOff;

Verb meta 'pronouns' 'nouns'
    *                                           -> Pronouns;

Verb meta 'quit' 'q//' 'die'
    *                                           -> Quit;

Verb meta 'recording'
    *                                           -> CommandsOn
    * 'on'                                      -> CommandsOn
    * 'off'                                     -> CommandsOff;

Verb meta 'replay'
    *                                           -> CommandsRead;

Verb meta 'restart'
    *                                           -> Restart;

Verb meta 'restore'
    *                                           -> Restore;

Verb meta 'save'
    *                                           -> Save;

Verb meta 'score'
    *                                           -> Score;

Verb meta 'fullscore' 'full'
    *                                           -> FullScore
    * 'score'                                   -> FullScore;

Verb meta 'script' 'transcript'
    *                                           -> ScriptOn
    * 'on'                                      -> ScriptOn
    * 'off'                                     -> ScriptOff;

Verb meta 'noscript' 'unscript'
    *                                           -> ScriptOff;

Verb meta 'verify'
    *                                           -> Verify;

Verb meta 'version'
    *                                           -> Version;

#Ifndef NO_PLACES;
Verb meta 'objects'
    *                                           -> Objects
    * 'tall'                                    -> ObjectsTall
    * 'wide'                                    -> ObjectsWide;
Verb meta 'places'
    *                                           -> Places
    * 'tall'                                    -> PlacesTall
    * 'wide'                                    -> PlacesWide;
#Endif; ! NO_PLACES

! ------------------------------------------------------------------------------
!  Debugging grammar
! ------------------------------------------------------------------------------

#Ifdef DEBUG;
Verb meta 'actions'
    *                                           -> ActionsOn
    * 'on'                                      -> ActionsOn
    * 'off'                                     -> ActionsOff;

Verb meta 'changes'
    *                                           -> ChangesOn
    * 'on'                                      -> ChangesOn
    * 'off'                                     -> ChangesOff;

Verb meta 'gonear'
    * anynumber                                 -> GoNear
    * noun                                      -> GoNear;


Verb meta 'goto'
    * anynumber                                 -> Goto;

Verb meta 'random'
    *                                           -> Predictable;

Verb meta 'routines' 'messages'
    *                                           -> RoutinesOn
    * 'on'                                      -> RoutinesOn
    * 'verbose'                                 -> RoutinesVerbose
    * 'off'                                     -> RoutinesOff;

Verb meta 'scope'
    *                                           -> Scope
    * anynumber                                 -> Scope
    * noun                                      -> Scope;

Verb meta 'showdict' 'dict'
    *                                           -> ShowDict
    * topic                                     -> ShowDict;

Verb meta 'showobj'
    *                                           -> ShowObj
    * anynumber                                 -> ShowObj
    * multi                                     -> ShowObj;

Verb meta 'showverb'
    * special                                   -> ShowVerb;

Verb meta 'timers' 'daemons'
    *                                           -> TimersOn
    * 'on'                                      -> TimersOn
    * 'off'                                     -> TimersOff;

Verb meta 'trace'
    *                                           -> TraceOn
    * number                                    -> TraceLevel
    * 'on'                                      -> TraceOn
    * 'off'                                     -> TraceOff;

Verb meta 'abstract'
    * anynumber 'to' anynumber                  -> XAbstract
    * noun 'to' noun                            -> XAbstract;

Verb meta 'purloin'
    * anynumber                                 -> XPurloin
    * multi                                     -> XPurloin;

Verb meta 'tree'
    *                                           -> XTree
    * anynumber                                 -> XTree
    * noun                                      -> XTree;

#Ifdef TARGET_GLULX;
Verb meta 'glklist'
    *                                           -> Glklist;
#Endif; ! TARGET_

#Endif; ! DEBUG

! ------------------------------------------------------------------------------
!  And now the game verbs.
! ------------------------------------------------------------------------------

[ ADirection; if (noun in Compass) rtrue; rfalse; ];


! ------------------------------------------------------------------------------
!  This routine is no longer used here, but provided to help existing games
!  which use it as a general parsing routine:

[ ConTopic w;
    consult_from = wn;
    do w = NextWordStopped();
    until (w == -1 || (w == 'to' && action_to_be == ##Answer));
    wn--;
    consult_words = wn - consult_from;
    if (consult_words == 0) return -1;
    if (action_to_be == ##Answer or ##Ask or ##Tell) {
        w = wn; wn = consult_from; parsed_number = NextWord();
        if (parsed_number == 'the' && consult_words > 1) parsed_number = NextWord();
        wn = w;
        return 1;
    }
    return 0;
];

! ------------------------------------------------------------------------------
!  Final task: provide trivial routines if the user hasn't already:
! ------------------------------------------------------------------------------

Default Story           0;
Default Headline        0;
Default d_obj           NULL;
Default u_obj           NULL;

Stub AfterLife         0;
Stub AfterPrompt       0;
Stub Amusing           0;
Stub BeforeParsing     0;
Stub ChooseObjects     2;
Stub DarkToDark        0;
Stub DeathMessage      0;
Stub Epilogue          0;
Stub GamePostRoutine   0;
Stub GamePreRoutine    0;
Stub InScope           1;
Stub LookRoutine       0;
Stub NewRoom           0;
Stub ObjectDoesNotFit  2;
Stub ParseNumber       2;
Stub ParserError       1;
Stub PrintTaskName     1;
Stub PrintVerb         1;
Stub TimePasses        0;
Stub UnknownVerb       1;
Stub AfterSave         1;
Stub AfterRestore      1;

#Ifdef TARGET_GLULX;
Stub HandleGlkEvent    2;
Stub IdentifyGlkObject 4;
Stub InitGlkWindow     1;
#Endif; ! TARGET_GLULX

#Ifndef PrintRank;
[ PrintRank; "."; ];
#Endif;

#Ifndef ParseNoun;
[ ParseNoun obj; obj = obj; return -1; ];
#Endif;

#Ifdef INFIX;
Include "infix";
#Endif;

! ==============================================================================

Undef LIBRARY_STAGE; Constant LIBRARY_STAGE = AFTER_GRAMMAR;

#Ifnot;		! LIBRARY_STAGE < AFTER_GRAMMAR but ~= AFTER_VERBLIB
Message "Error: 'verblib' needs to be correctly included before including 'grammar'. This will cause a big number of errors!";
#Endif;

#Ifnot;		! LIBRARY_STAGE >= AFTER_GRAMMAR : already included
Message "Warning: 'grammar' included twice; ignoring second inclusion. (Ignore this if this is on purpose.)";
#Endif;

#Ifnot;		! LIBRARY_STAGE is not defined
Message "Error: 'parser', then 'verblib' need to be correctly included before including 'grammar'. This will cause a big number of errors!";
#Endif;

! ==============================================================================
