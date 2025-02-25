## libCEED: Navier-Stokes Example

This page provides a description of the Navier-Stokes example for the libCEED library, based on PETSc.

The Navier-Stokes problem solves the compressible Navier-Stokes equations in three dimensions using an explicit time integration.
The state variables are mass density, momentum density, and energy density.

The main Navier-Stokes solver for libCEED is defined in [`navierstokes.c`](navierstokes.c) with different problem definitions according to the application of interest.

Build by using:

`make`

and run with:

```
./navierstokes -ceed [ceed] -problem [problem type] -degree [degree]
```

## Runtime options

% inclusion-fluids-marker

The Navier-Stokes mini-app is controlled via command-line options.
The following options are common among all problem types:

:::{list-table} Common Runtime Options
:header-rows: 1

* - Option
  - Description
  - Default value

* - `-ceed`
  - CEED resource specifier
  - `/cpu/self/opt/blocked`

* - `-test`
  - Run in test mode
  - `false`

* - `-compare_final_state_atol`
  - Test absolute tolerance
  - `1E-11`

* - `-compare_final_state_filename`
  - Test filename
  -

* - `-problem`
  - Problem to solve (`advection`, `advection2d`, `density_current`, or `euler_vortex`)
  - `density_current`

* - `-implicit`
  - Use implicit time integartor formulation
  -

* - `-degree`
  - Polynomial degree of tensor product basis (must be >= 1)
  - `1`

* - `-qextra`
  - Number of extra quadrature points
  - `2`

* - `-viz_refine`
  - Use regular refinement for visualization
  - `0`

* - `-output_freq`
  - Frequency of output, in number of steps
  - `10`

* - `-continue`
  - Continue from previous solution
  - `0`

* - `-output_dir`
  - Output directory
  - `.`

* - `-dm_plex_box_faces`
  - Number of faces in each linear direction
  - `3,3,3`

* - `-snes_view`
  - View PETSc `SNES` nonlinear solver configuration
  -

* - `-log_view`
  - View PETSc performance log
  -

* - `-help`
  - View comprehensive information about run-time options
  -
:::

For the 2D advection problem, the following additional command-line options are available:

:::{list-table} Advection2D Runtime Options
:header-rows: 1

* - Option
  - Description
  - Default value
  - Unit

* - `-lx`
  - Length scale in x direction
  - `8000`
  - `m`

* - `-ly`
  - Length scale in y direction
  - `8000`
  - `m`

* - `-rc`
  - Characteristic radius of thermal bubble
  - `1000`
  - `m`

* - `-units_meter`
  - 1 meter in scaled length units
  - `1E-2`
  -

* - `-units_second`
  - 1 second in scaled time units
  - `1E-2`
  -

* - `-units_kilogram`
  - 1 kilogram in scaled mass units
  - `1E-6`
  -

* - `-strong_form`
  - Strong (1) or weak/integrated by parts (0) residual
  - `0`
  -

* - `-stab`
  - Stabilization method (`none`, `su`, or `supg`)
  - `none`
  -

* - `-CtauS`
  - Scale coefficient for stabilization tau (nondimensional)
  - `0`
  -

* - `-wind_type`
  - Wind type in Advection (`rotation` or `translation`)
  - `rotation`
  -

* - `-wind_translation`
  - Constant wind vector when `-wind_type translation`
  - `1,0,0`
  -

* - `-E_wind`
  - Total energy of inflow wind when `-wind_type translation`
  - `1E6`
  - `J`
:::

An example of the `rotation` mode can be run with:

```
./navierstokes -problem advection2d -wind_type rotation -implicit -stab supg
```

and the `translation` mode with:

```
./navierstokes -problem advection2d -wind_type translation -wind_translation 1,-.5
```

For the 3D advection problem, the following additional command-line options are available:

:::{list-table} Advection3D Runtime Options
:header-rows: 1

* - Option
  - Description
  - Default value
  - Unit

* - `-lx`
  - Length scale in x direction
  - `8000`
  - `m`

* - `-ly`
  - Length scale in y direction
  - `8000`
  - `m`

* - `-lz`
  - Length scale in z direction
  - `4000`
  - `m`

* - `-rc`
  - Characteristic radius of thermal bubble
  - `1000`
  - `m`

* - `-units_meter`
  - 1 meter in scaled length units
  - `1E-2`
  -

* - `-units_second`
  - 1 second in scaled time units
  - `1E-2`
  -

* - `-units_kilogram`
  - 1 kilogram in scaled mass units
  - `1E-6`
  -

* - `-strong_form`
  - Strong (1) or weak/integrated by parts (0) residual
  - `0`
  -

* - `-stab`
  - Stabilization method (`none`, `su`, or `supg`)
  - `none`
  -

* - `-CtauS`
  - Scale coefficient for stabilization tau (nondimensional)
  - `0`
  -

* - `-wind_type`
  - Wind type in Advection (`rotation` or `translation`)
  - `rotation`
  -

* - `-wind_translation`
  - Constant wind vector when `-wind_type translation`
  - `1,0,0`
  -

* - `-E_wind`
  - Total energy of inflow wind when `-wind_type translation`
  - `1E6`
  - `J`

* - `-bubble_type`
  - `sphere` (3D) or `cylinder` (2D)
  - `shpere`
  -

* - `-bubble_continuity`
  - `smooth`, `back_sharp`, or `thick`
  - `smooth`
  -
:::

An example of the `rotation` mode can be run with:

```
./navierstokes -problem advection -wind_type rotation -implicit -stab supg
```

and the `translation` mode with:

```
./navierstokes -problem advection -wind_type translation -wind_translation .5,-1,0
```

For the Isentropic Vortex problem, the following additional command-line options are available:

:::{list-table} Isentropic Vortex Runtime Options
:header-rows: 1

* - Option
  - Description
  - Default value
  - Unit

* - `-lx`
  - Length scale in x direction
  - `1000`
  - `m`

* - `-ly`
  - Length scale in y direction
  - `1000`
  - `m`

* - `-lz`
  - Length scale in z direction
  - `1`
  - `m`

* - `-center`
  - Location of vortex center
  - `(lx,ly,lz)/2`
  - `(m,m,m)`

* - `-units_meter`
  - 1 meter in scaled length units
  - `1E-2`
  -

* - `-units_second`
  - 1 second in scaled time units
  - `1E-2`
  -

* - `-mean_velocity`
  - Background velocity vector
  - `(1,1,0)`
  -

* - `-vortex_strength`
  - Strength of vortex < 10
  - `5`
  -
:::

This problem can be run with:

```
./navierstokes -problem euler_vortex -mean_velocity .5,-.8,0.
```

For the Density Current problem, the following additional command-line options are available:

:::{list-table} Euler Vortex Runtime Options
:header-rows: 1

* - Option
  - Description
  - Default value
  - Unit

* - `-lx`
  - Length scale in x direction
  - `8000`
  - `m`

* - `-ly`
  - Length scale in y direction
  - `8000`
  - `m`

* - `-lz`
  - Length scale in z direction
  - `4000`
  - `m`

* - `-center`
  - Location of bubble center
  - `(lx,ly,lz)/2`
  - `(m,m,m)`

* - `-dc_axis`
  - Axis of density current cylindrical anomaly, or `(0,0,0)` for spherically symmetric
  - `(0,0,0)`
  -

* - `-rc`
  - Characteristic radius of thermal bubble
  - `1000`
  - `m`

* - `-bc_wall`
  - Use wall boundary conditions on this list of faces
  - `-`
  -

* - `-bc_slip_x`
  - Use slip boundary conditions, for the x component, on this list of faces
  - `5,6`
  -

* - `-bc_slip_y`
  - Use slip boundary conditions, for the y component, on this list of faces
  - `3,4`
  -

* - `-bc_slip_z`
  - Use slip boundary conditions, for the z component, on this list of faces
  - `1,2`
  -

* - `-units_meter`
  - 1 meter in scaled length units
  - `1E-2`
  -

* - `-units_second`
  - 1 second in scaled time units
  - `1E-2`
  -

* - `-units_kilogram`
  - 1 kilogram in scaled mass units
  - `1E-6`
  -

* - `-units_Kelvin`
  - 1 Kelvin in scaled temperature units
  - `1`
  -

* - `-stab`
  - Stabilization method (`none`, `su`, or `supg`)
  - `none`
  -

* - `-theta0`
  - Reference potential temperature
  - `300`
  - `K`

* - `-thetaC`
  - Perturbation of potential temperature
  - `-15`
  - `K`

* - `-P0`
  - Atmospheric pressure
  - `1E5`
  - `Pa`

* - `-N`
  - Brunt-Vaisala frequency
  - `0.01`
  - `1/s`

* - `-cv`
  - Heat capacity at constant volume
  - `717`
  - `J/(kg K)`

* - `-cp`
  - Heat capacity at constant pressure
  - `1004`
  - `J/(kg K)`

* - `-g`
  - Gravitational acceleration
  - `9.81`
  - `m/s^2`

* - `-lambda`
  - Stokes hypothesis second viscosity coefficient
  - `-2/3`
  -

* - `-mu`
  - Shear dynamic viscosity coefficient
  - `75`
  -  `Pa s`

* - `-k`
  - Thermal conductivity
  - `0.02638`
  - `W/(m K)`
:::

For the case of a square/cubic mesh, the list of face indices to be used with `-bc_wall` and/or `-bc_slip_x`, `-bc_slip_y`, and `-bc_slip_z` are:

* 2D:
  - faceMarkerBottom = 1
  - faceMarkerRight  = 2
  - faceMarkerTop    = 3
  - faceMarkerLeft   = 4
* 3D:
  - faceMarkerBottom = 1
  - faceMarkerTop    = 2
  - faceMarkerFront  = 3
  - faceMarkerBack   = 4
  - faceMarkerRight  = 5
  - faceMarkerLeft   = 6

This problem can be run with:

```
./navierstokes -problem density_current -dm_plex_box_faces 16,1,8 -degree 1 -lx 2000 -ly 125 -lz 1000 -rc 400. -bc_wall 1,2,5,6 -bc_slip_y 3,4 -viz_refine 2
```
