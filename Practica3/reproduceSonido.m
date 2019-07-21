% Mario Ruiz Calvo. 27/05/17
function[y]=reproduceSonido(signal,fMuest, resol, t_ini, t_fin)
% Obtener el tamaño de la señal.
[n,~] = size(signal);
% Si no se especifican el tiempo de inicio y fin, se reproduce el sonido
% completo.
if nargin == 3
    i_t_ini=1;
    i_t_fin=n;
% Si se especifican el tiempo de inicio y fin calcular los indices
% correspondientes en la señal. Para calcularlos multiplicar los segundos
% por la frecuencia.
else
    i_t_ini=t_ini*fMuest;
    i_t_fin=t_fin*fMuest;
end
% Si el tiempo de inicio es negativo o mayor a la duración del sonido, se
% reproduce desde el principio.
if i_t_ini<1 || i_t_ini>n 
    i_t_ini=1;
end
% Si el tiempo de fin es negativo o mayor a la duración del sonido, se
% reproduce hasta el final.
if i_t_fin<1 || i_t_fin>n 
    i_t_fin=n;
end
% Redondear los indices para el caso en que se introduzcan segundos con 
% decimales.
i_t_ini=round(i_t_ini);
i_t_fin=round(i_t_fin);
% Reproducir el sonido. Indexando la matriz con los valores calculados
% antes (siempre serán valores válidos), conseguimos que se reproduzca en
% el intervalo que queramos.
sound(signal(i_t_ini:i_t_fin),fMuest,resol);
end

