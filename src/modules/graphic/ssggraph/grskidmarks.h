#ifndef _GRSKIDMARKS_H_
#define _GRSKIDMARKS_H_

#define MAXPOINT_BY_STRIP 3000
#define MAXSTRIP_BYWHEEL  10
#define DIST_INTERVAL     0.2f

#define SKID_UNUSED  1
#define SKID_BEGIN   2
#define SKID_RUNNING 3
#define SKID_STOPPED 4

typedef struct 
{
  ssgVertexArray * vtx[MAXSTRIP_BYWHEEL]; /* the strips */
  ssgVtxTableShadow    * vta[MAXSTRIP_BYWHEEL];
  int state[MAXSTRIP_BYWHEEL];
  int size[MAXSTRIP_BYWHEEL];
  int running_skid;
  int next_skid;
  int last_state_of_skid;
  int skid_full;

}tgrSkidStrip;

typedef struct 
{
  ssgVtxTable *base; /* to remember the pos of the wheel line before transform */
  tgrSkidStrip   strips[4]; /* the strips of the four wheels*/
}tgrSkidmarks;

extern void initSkidmarks(tCarElt *car);
extern void grUpdateSkidmarks(tCarElt *car);
extern void shutdownSkidmarks (tCarElt *car);
extern void grDrawSkidmarks (tCarElt *car);


#endif /* _GRSKIDMARKS_*/
