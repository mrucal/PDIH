% Mario Ruiz Calvo. 27/05/17
% Calcular el valor decimal de un número hexadecimal pasado como vector en
% little endian. Es decir, el número expresado como hex = [50 7F 02 00]
% (0x00027f50) se corresponde con el valor decimal 163664.
function [ decimal ] = hexa_a_decimal( hexa )
    decimal = hexa(1);
    n = 2;    
    for i = 2 : length(hexa)
        decimal = decimal + (hexa(i) * 16^n);
        n=n+2;
    end
end

