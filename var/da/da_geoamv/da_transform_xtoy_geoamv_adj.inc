subroutine da_transform_xtoy_geoamv_adj (grid, iv, jo_grad_y, jo_grad_x)

   !-------------------------------------------------------------------------
   ! Purpose: X to Y Transpose operator for Geo. AMVs
   !    Updated for Analysis on Arakawa-C grid
   !    Author: Syed RH Rizvi,  MMM/ESSL/NCAR,  Date: 10/22/2008
   !-------------------------------------------------------------------------

   implicit none
   type(domain),  intent(in)    :: grid
   type (iv_type), intent(in)    :: iv          ! obs. inc vector (o-b).
   type (y_type) , intent(in)    :: jo_grad_y   ! grad_y(jo)
   type (x_type) , intent(inout) :: jo_grad_x   ! grad_x(jo)

   integer           :: n, k     ! Loop counter.
   real, allocatable :: u(:,:)
   real, allocatable :: v(:,:)
   real, allocatable :: ub(:,:)
   real, allocatable :: vb(:,:)

   if (trace_use_dull) call da_trace_entry("da_transform_xtoy_geoamv_adj")
 
   allocate (u(iv%info(geoamv)%max_lev,iv%info(geoamv)%n1:iv%info(geoamv)%n2))
   allocate (v(iv%info(geoamv)%max_lev,iv%info(geoamv)%n1:iv%info(geoamv)%n2))

   allocate (ub(iv%info(geoamv)%max_lev,iv%info(geoamv)%n1:iv%info(geoamv)%n2))
   allocate (vb(iv%info(geoamv)%max_lev,iv%info(geoamv)%n1:iv%info(geoamv)%n2))

   call da_interp_lin_3d (grid%xb%u, iv%info(geoamv), ub)
   call da_interp_lin_3d (grid%xb%v, iv%info(geoamv), vb)

   do n=iv%info(geoamv)%n1,iv%info(geoamv)%n2
      do k = 1, iv%info(geoamv)%levels(n)
          if(wind_sd_geoamv) then
             call da_uv_to_sd_adj(jo_grad_y%geoamv(n)%u(k), &
                                  jo_grad_y%geoamv(n)%v(k), u(k,n), v(k,n), ub(k,n), vb(k,n))
          else
             u(k,n) = jo_grad_y%geoamv(n)%u(k)
             v(k,n) = jo_grad_y%geoamv(n)%v(k)
          end if
      end do
   end do

#ifdef A2C
   call da_interp_lin_3d_adj (jo_grad_x%u, iv%info(geoamv), u,'u')
   call da_interp_lin_3d_adj (jo_grad_x%v, iv%info(geoamv), v,'v')
#else
   call da_interp_lin_3d_adj (jo_grad_x%u, iv%info(geoamv), u)
   call da_interp_lin_3d_adj (jo_grad_x%v, iv%info(geoamv), v)
#endif

   deallocate (u)
   deallocate (v)
   deallocate (ub)
   deallocate (vb)

   if (trace_use_dull) call da_trace_exit("da_transform_xtoy_geoamv_adj")

end subroutine da_transform_xtoy_geoamv_adj


