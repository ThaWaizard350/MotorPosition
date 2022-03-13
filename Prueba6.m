clc
close all
%k=70
%Subir datos
datos=importdata('Prueba6.xlsx');
entradacto=4*ones(4000,1);
voltaje=datos(:,1);
s=tf('s');
salidacto=voltaje;
plot(voltaje)

%Promedio Movil
m=40;
filtro=(1/m)*ones(1,m); %Promedio Movil
Entrada=entradacto;
S=salidacto;
S=conv(S,filtro);
Salida=S(1:4000);

figure,
hold on
plot(Salida)
plot(Entrada)
hold off

% %Funcion de transferencia Toolbox
% TF =(0.04161*s^4 + 0.2043*s^3 + 1.127*s^2 + 0.4426*s + 2.141)/(s^5 + 2.17*s^4 + 6.155*s^3 + 7.242*s^2 + 6.105*s + 2.144);
% 
% %Discretizacion
% tfd=c2d(TF,0.004);
% figure,
% step(4*tfd)