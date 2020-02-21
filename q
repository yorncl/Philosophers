GETTIMEOFDAY(L2i)nux Programmer's ManuGaElTTIMEOFDAY(2)

NNAAMMEE
       gettimeofday,  settimeofday  -  get  / set
       time

SSYYNNOOPPSSIISS
       ##iinncclluuddee <<ssyyss//ttiimmee..hh>>

       iinntt ggeettttiimmeeooffddaayy((ssttrruucctt ttiimmeevvaall **_t_v,, ssttrruucctt ttiimmeezzoonnee **_t_z));;

       iinntt sseettttiimmeeooffddaayy((ccoonnsstt ssttrruucctt ttiimmeevvaall **_t_v,, ccoonnsstt ssttrruucctt ttiimmeezzoonnee **_t_z));;

   Feature Test Macro Requirements for glibc (see
   ffeeaattuurree__tteesstt__mmaaccrrooss(7)):

       sseettttiimmeeooffddaayy():
           Since glibc 2.19:
               _DEFAULT_SOURCE
           Glibc 2.19 and earlier:
               _BSD_SOURCE

DDEESSCCRRIIPPTTIIOONN
       The  functions ggeettttiimmeeooffddaayy() and sseettttiimmee‐‐
       ooffddaayy() can get and set the time  as  well
       as  a  timezone.   The  _t_v  argument  is a
       _s_t_r_u_c_t   _t_i_m_e_v_a_l    (as    specified    in
       _<_s_y_s_/_t_i_m_e_._h_>):

           struct timeval {
               time_t      tv_sec;     /* seconds */
               suseconds_t tv_usec;    /* microseconds */
           };

       and   gives  the  number  of  seconds  and
       microseconds   since   the   Epoch    (see
       ttiimmee(2)).   The  _t_z  argument  is a _s_t_r_u_c_t
       _t_i_m_e_z_o_n_e:

           struct timezone {
               int tz_minuteswest;     /* minutes west of Greenwich */
               int tz_dsttime;         /* type of DST correction */
           };

       If either _t_v or _t_z  is  NULL,  the  corre‐
       sponding structure is not set or returned.
       (However, compilation warnings will result
       if _t_v is NULL.)

       The use of the _t_i_m_e_z_o_n_e structure is obso‐
       lete; the _t_z argument should  normally  be
       specified as NULL.  (See NOTES below.)

       Under Linux, there are some peculiar "warp
       clock" semantics associated with the  sseett‐‐
       ttiimmeeooffddaayy()  system  call  if  on the very
       first call (after booting) that has a non-
       NULL  _t_z argument, the _t_v argument is NULL
       and the _t_z___m_i_n_u_t_e_s_w_e_s_t field  is  nonzero.
       (The  _t_z___d_s_t_t_i_m_e  field should be zero for
       this case.)  In such a case it is  assumed
       that  the CMOS clock is on local time, and
       that it has  to  be  incremented  by  this
       amount  to  get UTC system time.  No doubt
       it is a bad idea to use this feature.

RREETTUURRNN VVAALLUUEE
       ggeettttiimmeeooffddaayy() and sseettttiimmeeooffddaayy() return 0
       for  success,  or -1 for failure (in which
       case _e_r_r_n_o is set appropriately).

EERRRROORRSS
       EEFFAAUULLTT One of _t_v or _t_z pointed outside the
              accessible address space.

       EEIINNVVAALL Timezone  (or  something  else)  is
              invalid.

       EEPPEERRMM  The calling  process  has  insuffi‐
              cient  privilege to call sseettttiimmeeooff‐‐
              ddaayy(); under Linux the CCAAPP__SSYYSS__TTIIMMEE
              capability is required.

CCOONNFFOORRMMIINNGG TTOO
       SVr4, 4.3BSD.  POSIX.1-2001 describes ggeett‐‐
       ttiimmeeooffddaayy()   but   not    sseettttiimmeeooffddaayy().
       POSIX.1-2008 marks ggeettttiimmeeooffddaayy() as obso‐
       lete, recommending the use  of  cclloocckk__ggeett‐‐
       ttiimmee(2) instead.

NNOOTTEESS
       The  time  returned  by  ggeettttiimmeeooffddaayy() _i_s
       affected by  discontinuous  jumps  in  the
       system  time (e.g., if the system adminis‐
       trator manually changes the system  time).
       If  you  need  a  monotonically increasing
       clock, see cclloocckk__ggeettttiimmee(2).

       Macros for operating on _t_i_m_e_v_a_l structures
       are described in ttiimmeerraadddd(3).

       Traditionally,   the   fields   of  _s_t_r_u_c_t
       _t_i_m_e_v_a_l were of type _l_o_n_g.

   CC lliibbrraarryy//kkeerrnneell ddiiffffeerreenncceess
       On some architectures,  an  implementation
       of   ggeettttiimmeeooffddaayy()  is  provided  in  the
       vvddssoo(7).

   TThhee ttzz__ddssttttiimmee ffiieelldd
       On a non-Linux  kernel,  with  glibc,  the
       _t_z___d_s_t_t_i_m_e  field  of _s_t_r_u_c_t _t_i_m_e_z_o_n_e will
       be set to a nonzero  value  by  ggeettttiimmeeooff‐‐
       ddaayy() if the current timezone has ever had
       or  will  have  a  daylight  saving   rule
       applied.  In this sense it exactly mirrors
       the meaning of ddaayylliigghhtt(3) for the current
       zone.   On  Linux, with glibc, the setting
       of the _t_z___d_s_t_t_i_m_e field of _s_t_r_u_c_t _t_i_m_e_z_o_n_e
       has  never  been used by sseettttiimmeeooffddaayy() or
       ggeettttiimmeeooffddaayy().  Thus,  the  following  is
       purely of historical interest.

       On  old systems, the field _t_z___d_s_t_t_i_m_e con‐
       tains  a  symbolic  constant  (values  are
       given  below) that indicates in which part
       of the year Daylight  Saving  Time  is  in
       force.   (Note:  this  value  is  constant
       throughout the year: it does not  indicate
       that  DST  is in force, it just selects an
       algorithm.)   The  daylight  saving   time
       algorithms defined are as follows:

           DDSSTT__NNOONNEE     /* not on DST */
           DDSSTT__UUSSAA      /* USA style DST */
           DDSSTT__AAUUSSTT     /* Australian style DST */
           DDSSTT__WWEETT      /* Western European DST */
           DDSSTT__MMEETT      /* Middle European DST */
           DDSSTT__EEEETT      /* Eastern European DST */
           DDSSTT__CCAANN      /* Canada */
           DDSSTT__GGBB       /* Great Britain and Eire */
           DDSSTT__RRUUMM      /* Romania */
           DDSSTT__TTUURR      /* Turkey */
           DDSSTT__AAUUSSTTAALLTT  /* Australian style with shift in 1986 */

       Of course it turned out that the period in
       which Daylight Saving  Time  is  in  force
       cannot be given by a simple algorithm, one
       per country; indeed, this period is deter‐
       mined  by  unpredictable  political  deci‐
       sions.  So  this  method  of  representing
       timezones has been abandoned.

SSEEEE AALLSSOO
       ddaattee(1),   aaddjjttiimmeexx(2),  cclloocckk__ggeettttiimmee(2),
       ttiimmee(2), ccttiimmee(3), ffttiimmee(3),  ttiimmeerraadddd(3),
       ccaappaabbiilliittiieess(7),     ttiimmee(7),     vvddssoo(7),
       hhwwcclloocckk(8)

CCOOLLOOPPHHOONN
       This page is part of release 4.15  of  the
       Linux _m_a_n_-_p_a_g_e_s project.  A description of
       the project, information  about  reporting
       bugs, and the latest version of this page,
       can          be          found          at
       https://www.kernel.org/doc/man-pages/.

Linux               2017-09-15    GETTIMEOFDAY(2)
