c     This is the include file that defines what is necessary for the
c     generic FORTRAN interface with REAL*8 (double) data.

      COMPLEX*16 II(16),Fbar(12),F(12),E(3),G(6),H
      COMPLEX*16 IIbold(16,3),Fbold(12,4),Ebold(3,4),Gbold(6,4),Hbold(2)

c     This common block matches a C struct defined in the wrapper code
c     fevaluate.c:
      COMMON /tvilresults/ II,Fbar,F,E,G,H,IIbold,Fbold,Ebold,Gbold,Hbold

c     This value is used to check for data size compatibility with the 
c     library when tsilfevaluate is called:
      INTEGER rsize
      COMMON /tvilrsize/ rsize
      DATA rsize/8/

c     Variables for indexing arrays:
      INTEGER uvx,xyz,uxy,vxz,uwz,vwy,uwy,vwz
      INTEGER vyz,wxy,uvz,uwx,uyz,wxz,uvy,vwx
      PARAMETER(uvx=1,xyz=2,uxy=3,vxz=4,uwz=5,vwy=6,uwy=7,vwz=8)
      PARAMETER(vyz=9,wxy=10,uvz=11,uwx=12,uyz=13,wxz=14,uvy=15,vwx=16)

      INTEGER wuxy,wvxz,xuwy,xvwz,uvyz,uwxy
      INTEGER yuvz,yuwx,vuyz,vwxz,zuvy,zvwx
      PARAMETER(wuxy=1,wvxz=2,xuwy=3,xvwz=4,uvyz=5,uwxy=6,yuvz=7,yuwx=8)
      PARAMETER(vuyz=9,vwxz=10,zuvy=11,zvwx=12)

      INTEGER wuzvy,xuvyz,uvxwz,yvwxz,vuxwy,zuwxy
      PARAMETER(wuzvy=1,xuvyz=2,uvxwz=3,yvwxz=4,vuxwy=5,zuwxy=6)