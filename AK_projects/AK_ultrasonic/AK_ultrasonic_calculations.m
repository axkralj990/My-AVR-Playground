%% Calculations for AVR ultrasonic beeper program
% Written by: Aleksij Kraljic
% September 26, 2016
clear all; close all; clc;

%% INPUT ========================================
freq_far = 1; %Hz
freq_near = 25; %Hz

dist_far = 100; %cm
dist_near = 20; %cm

%% CALCULATIONS =================================
y2 = freq_far; x2 = dist_far;
y1 = freq_near; x1 = dist_near;

% slope
k = (y2-y1)/(x2-x1);

% y-intersect
n = y1-k*x1;

dist = linspace(dist_near,dist_far,100);
echo = dist.*58;

freq = k.*dist+n; %Hz
period = 1000./freq; %ms

no_obstable_period = 1000./(k*(12/58)+n);

%% OUTPUT =======================================
fprintf('beep_period = 1000/((%0.4f / CONVERT2CM)*(float)echo_time+%0.2f);\n',k,n);
fprintf('No obstacle beep_period = %0.0f ms\n',ceil(no_obstable_period));
fprintf('Near distance period = %0.0f ms\n',min(period));
fprintf('Far distance period = %0.0f ms\n',0.8*max(period));

figure(1);
plot(dist,freq,'LineWidth',2); grid on;
xlabel('Distance [cm]');
ylabel('Frequency [Hz]');

figure(2);
plot(dist,period,'LineWidth',2); grid on;
xlabel('Distance [cm]');
ylabel('Period [ms]');

figure(3);
plot(echo,period,'LineWidth',2); grid on;
xlabel('Echo [ms]');
ylabel('Period [ms]');
%% ==============================================