% Define the 5-DOF robot using DH parameters
L1 = Link('d', 0.2, 'a', 0, 'alpha', pi/2); % Link 1
L2 = Link('d', 0, 'a', 0.5, 'alpha', 0);   % Link 2
L3 = Link('d', 0, 'a', 0.3, 'alpha', -pi/2); % Link 3
L4 = Link('d', 0.15, 'a', 0, 'alpha', pi/2); % Link 4
L5 = Link('d', 0.1, 'a', 0, 'alpha', 0);   % Link 5

robot = SerialLink([L1 L2 L3 L4 L5], 'name', '5DOF Arm');

% Define tool transform
robot.tool = SE3(0, 0, 0.1); % 100mm extension in z-direction

% Define canonical configurations
qz = [0 0 0 0 0]; % Zero angle
qr = [pi/4 -pi/4 0 pi/6 0]; % Ready position
qs = [0 pi/2 -pi/2 0 pi/4]; % Stretch position

% Perform forward kinematics for canonical configurations
T_zero = robot.fkine(qz);
T_ready = robot.fkine(qr);
T_stretch = robot.fkine(qs);

% Display results
disp('Zero angle configuration:');
disp(T_zero);
disp('Ready configuration:');
disp(T_ready);
disp('Stretch configuration:');
disp(T_stretch);

% Graphically display configurations
figure(1);
robot.plot3d(qz);
title('Zero angle configuration');
figure(2);
robot.plot3d(qr);
title('Ready configuration');
figure(3);
robot.plot3d(qs);
title('Stretch configuration');

% Reset tool transform
robot.tool = SE3();

% Define a target pose for inverse kinematics
T_target = SE3(0.3, 0.2, 0.4) * SE3.Ry(pi/3);

% Perform inverse kinematics
q_inv = robot.ikine(T_target, 'mask', [1 1 1 0 0 0]); % Mask for 5 DOF

% Display the results of inverse kinematics
disp('Inverse kinematics solution:');
disp(q_inv);

% Check for an unreachable point
unreachable_point = SE3(2, 2, 2); % Outside workspace
q_unreachable = robot.ikine(unreachable_point, 'mask', [1 1 1 0 0 0]);
disp('Result for unreachable point:');
disp(q_unreachable);

% Define two poses for trajectory
T1 = SE3(0.4, 0, 0.3) * SE3.Rz(pi/2);
T2 = SE3(-0.4, 0, 0.3) * SE3.Rz(-pi/2);

% Compute joint angles for the poses
q1 = robot.ikine(T1, 'mask', [1 1 1 0 0 0]);
q2 = robot.ikine(T2, 'mask', [1 1 1 0 0 0]);

% Create a trajectory
t = [0:0.05:2]';
q_traj = jtraj(q1, q2, t);

% Animate the trajectory
robot.plot3d(q_traj);
