c     Compile as: gfortran ftest.f -L. -ltsil

      PROGRAM ftest

      INCLUDE '3vil_fort.inc'

      REAL*8 u0,v0,w0,x0,y0,z0,qq
      INTEGER i,j

      u0=1.0
      v0=2.0
      w0=3.0
      x0=4.0
      y0=5.0
      z0=6.0
      qq=1.0

      CALL tvilfevaluate (u0,v0,w0,x0,y0,z0,qq)

      print *,'u  = ', u0
      print *,'v  = ', v0
      print *,'w  = ', w0
      print *,'x  = ', x0
      print *,'y  = ', y0
      print *,'z  = ', z0
      print *,'qq = ', qq
      print *

      print *,'(* Bold Functions: *)'
      do j=1,4
         print *,'Ewuxy(',j-1,') = ', Ebold(1,j)
      end do
      print *
      do j=1,4
         print *,'Evwxz(',j-1,') = ', Ebold(2,j)
      end do
      print *
      do j=1,4
         print *,'Euvyz(',j-1,') = ', Ebold(3,j)
      end do
      print *

      do j=1,4
         print *,'Fwuxy(',j-1,') = ', Fbold(wuxy,j)
      end do
      print *
      do j=1,4
         print *,'Fwvxz(',j-1,') = ', Fbold(wvxz,j)
      end do
      print *
      do j=1,4
         print *,'Fxuwy(',j-1,') = ', Fbold(xuwy,j)
      end do
      print *
      do j=1,4
         print *,'Fxvwz(',j-1,') = ', Fbold(xvwz,j)
      end do
      print *
      do j=1,4
         print *,'Fuvyz(',j-1,') = ', Fbold(uvyz,j)
      end do
      print *
      do j=1,4
         print *,'Fuwxy(',j-1,') = ', Fbold(uwxy,j)
      end do
      print *
      do j=1,4
         print *,'Fyuvz(',j-1,') = ', Fbold(yuvz,j)
      end do
      print *
      do j=1,4
         print *,'Fyuwx(',j-1,') = ', Fbold(yuwx,j)
      end do
      print *
      do j=1,4
         print *,'Fvuyz(',j-1,') = ', Fbold(vuyz,j)
      end do
      print *
      do j=1,4
         print *,'Fvwxz(',j-1,') = ', Fbold(vwxz,j)
      end do
      print *
      do j=1,4
         print *,'Fzuvy(',j-1,') = ', Fbold(zuvy,j)
      end do
      print *
      do j=1,4
         print *,'Fzvwx(',j-1,') = ', Fbold(zvwx,j)
      end do
      print *

      do j=1,4
         print *,'Gwuzvy(',j-1,') = ', Gbold(wuzvy,j)
      end do
      print *
      do j=1,4
         print *,'Gxuvyz(',j-1,') = ', Gbold(xuvyz,j)
      end do
      print *
      do j=1,4
         print *,'Guvxwz(',j-1,') = ', Gbold(uvxwz,j)
      end do
      print *
      do j=1,4
         print *,'Gyvwxz(',j-1,') = ', Gbold(yvwxz,j)
      end do
      print *
      do j=1,4
         print *,'Gvuxwy(',j-1,') = ', Gbold(vuxwy,j)
      end do
      print *
      do j=1,4
         print *,'Gzuwxy(',j-1,') = ', Gbold(zuwxy,j)
      end do
      print *

      do j=1,2
         print *,'H(',j-1,') = ', Hbold(j)
      end do
      print *

      print *,'(* Basis Functions: *)'
      print *,'Iuvx = ', II(uvx)
      print *,'Ixyz = ', II(xyz)
      print *,'Iuxy = ', II(uxy)
      print *,'Ivxz = ', II(vxz)
      print *,'Iuwz = ', II(uwz)
      print *,'Ivwy = ', II(vwy)
      print *,'Iuwy = ', II(uwy)
      print *,'Ivwz = ', II(vwz)
      print *,'Ivyz = ', II(vyz)
      print *,'Iwxy = ', II(wxy)
      print *,'Iuvz = ', II(uvz)
      print *,'Iuwx = ', II(uwx)
      print *,'Iuyz = ', II(uyz)
      print *,'Iwxz = ', II(wxz)
      print *,'Iuvy = ', II(uvy)
      print *,'Ivwx = ', II(vwx)

      print *
      print *,'Ewuxy = ', E(1)
      print *,'Evwxz = ', E(2)
      print *,'Euvyz = ', E(3)

      print *
      print *,'Fwuxy = ', F(wuxy)
      print *,'Fwvxz = ', F(wvxz)
      print *,'Fxuwy = ', F(xuwy)
      print *,'Fxvwz = ', F(xvwz)
      print *,'Fuvyz = ', F(uvyz)
      print *,'Fuwxy = ', F(uwxy)
      print *,'Fyuvz = ', F(yuvz)
      print *,'Fyuwx = ', F(yuwx)
      print *,'Fvuyz = ', F(vuyz)
      print *,'Fvwxz = ', F(vwxz)
      print *,'Fzuvy = ', F(zuvy)
      print *,'Fzvwx = ', F(zvwx)

      print *
      print *,'FBARwuxy = ', FBAR(wuxy)
      print *,'FBARwvxz = ', FBAR(wvxz)
      print *,'FBARxuwy = ', FBAR(xuwy)
      print *,'FBARxvwz = ', FBAR(xvwz)
      print *,'FBARuvyz = ', FBAR(uvyz)
      print *,'FBARuwxy = ', FBAR(uwxy)
      print *,'FBARyuvz = ', FBAR(yuvz)
      print *,'FBARyuwx = ', FBAR(yuwx)
      print *,'FBARvuyz = ', FBAR(vuyz)
      print *,'FBARvwxz = ', FBAR(vwxz)
      print *,'FBARzuvy = ', FBAR(zuvy)
      print *,'FBARzvwx = ', FBAR(zvwx)

      print *
      print *,'Gwuzvy = ', G(wuzvy)
      print *,'Gxuvyz = ', G(xuvyz)
      print *,'Guvxwz = ', G(uvxwz)
      print *,'Gyvwxz = ', G(yvwxz)
      print *,'Gvuxwy = ', G(vuxwy)
      print *,'Gzuwxy = ', G(zuwxy)

      print *
      print *, 'H = ', H

      END PROGRAM ftest
