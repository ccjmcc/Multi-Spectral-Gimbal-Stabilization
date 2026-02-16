% MSG-600 Stabilization Loop Simulation
% Copyright (c) 2026 GimbalSystems
% 
% Simple 1-DoF plant model to tune PID gains before deployment.

clear; clc;

% System Parameters
J = 0.005; % Inertia (kg*m^2)
B = 0.001; % Damping
K_motor = 0.08; % Torque constant

% PID Gains (Initial Guess)
Kp = 12.5;
Ki = 0.05;
Kd = 0.008;

% Simulation Loop
dt = 0.001; % 1kHz loop
T_sim = 2.0;
N = T_sim/dt;

ref = 1.0; % Target angle (rad)
theta = 0;
omega = 0;
integral = 0;
prev_err = 0;

time = 0:dt:T_sim-dt;
response = zeros(1, N);

for i = 1:N
    % Feedback
    error = ref - theta;
    integral = integral + error*dt;
    derivative = (error - prev_err)/dt;
    
    % PID Output (Torque)
    u = Kp*error + Ki*integral + Kd*derivative;
    
    % Plant Dynamics
    alpha = (K_motor*u - B*omega)/J;
    omega = omega + alpha*dt;
    theta = theta + omega*dt;
    
    response(i) = theta;
    prev_err = error;
end

plot(time, response, 'LineWidth', 2);
title('Step Response of Pitch Axis');
xlabel('Time (s)');
ylabel('Angle (rad)');
grid on;

fprintf('Steady State Error: %.5f\n', ref - theta);

% Note: For full 3-axis coupling simulation with gimbal lock prevention,
% please use the Simulink models provided in the TwinsGlow SDK.
