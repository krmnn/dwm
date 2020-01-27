/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 20;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/

static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "Source Code Pro SemiBold:size=11", "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_darkgray[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray[]       = "#bbbbbb";
static const char col_white[]       = "#eeeeee";
static const char col_blue[]        = "#3465a4";
static const char col_red[]        = "#cc0000";
static const char *colors[][6]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray, col_darkgray, col_gray2 },
    [SchemeSel]  = { col_white, col_blue,  col_red  },
    [SchemeBar]  = { col_gray, col_darkgray,  col_white  },
    [SchemeTaskSel]  = { col_white, col_red,  col_red  },
    [SchemeTaskNorm]  = { col_darkgray, col_white,  col_white  },
    [SchemeLayout]  = { col_white, col_darkgray,  col_white  },
};

/* tagging */
/*
 * 1 web: browse the interwebs, read articles
 * 2 mail: firefox with gmail 
 * 3 cal: firefox with gmail 
 * 4 chat: firefox with gmail 
 * 5 docu: firefox with documentation/confluence 
 * 6 dev: $n termite terminals in tile layout, vim for programming, git + ci pipelines for devops tasks
 * 7 ssh: $n termite terminals with remote sessions, manually managing machines
 * 8 spare
 */
static const char *tags[] = { "1 web", "2 mail", "3 chat", "4 cal", "5 docu", "6 dev", "7 remote", "8 misc" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class         instance    title       tags mask     isfloating   monitor */
    { "Gimp",        NULL,       NULL,       0,            1,           -1 },
    { NULL,          NULL,       "Save As",  0,            1,           -1 },
    { "Firefox",     NULL,       NULL,       1 << 0,       0,           -1 },
    { "thunderbird", NULL,       NULL,       1 << 1,       0,           -1 },
    { "Thunderbird", NULL,       NULL,       1 << 1,       0,           -1 },
    { "gmail",       NULL,       NULL,       1 << 1,       0,           -1 },
    { "chat",        NULL,       NULL,       1 << 2,       0,           -1 },
    { "Discord",     NULL,       NULL,       1 << 2,       0,           -1 },
    //{ "Termite",     NULL,       NULL,       1 << 4,       0,           -1 },
    { "ssh",         NULL,       NULL,       1 << 6,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[t]",      tile },    /* first entry is default */
    { "[m]",      monocle },
    { "[f]",      NULL },    /* no layout function means floating behavior */
    { NULL,      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ 0,                  KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY,             KEY,      view,           {.ui = 1 << TAG} }, \
{ WINKEY,             KEY,      tag,            {.ui = 1 << TAG} }, \
//{ WINKEY,             KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "rofi", "-show", "run", NULL };
static const char *termcmd[]  = { "termite", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    TAGKEYS(                        XK_F1,                      0)
    TAGKEYS(                        XK_F2,                      1)
    TAGKEYS(                        XK_F3,                      2)
    TAGKEYS(                        XK_F4,                      3)
    TAGKEYS(                        XK_F5,                      4)
    TAGKEYS(                        XK_F6,                      5)
    TAGKEYS(                        XK_F7,                      6)
    TAGKEYS(                        XK_F8,                      7)
    { 0,                            XK_F9,     spawn,          {.v = termcmd } },
    { 0,                            XK_F10,    spawn,          {.v = dmenucmd } },
    { 0,                            XK_F12,    view,           {0} }, // last view
    // focus & zoom & kill clients
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_space,   zoom,           {0} },
    { 0,                            XK_End,    killclient,     {0} },
    // layout
    //{ 0,                            XK_Home,  setlayout,      {0} },
	{ 0,                            XK_Home,  cyclelayout,    {.i = +1 } },
    { MODKEY,                       XK_Home,  togglefloating, {0} },
    // master area
    { MODKEY,                       XK_period,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_comma,      incnmaster,     {.i = -1 } },
    // xinerama / multihead setups / presentations
    //{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    //{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    //{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    //{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    // dwm
    { MODKEY,                       XK_q,      quit,           {0} },
    // disabled
    //{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    //{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    //{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    //{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    //{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    //{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    //{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    //{ MODKEY,                       XK_b,      togglebar,      {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

