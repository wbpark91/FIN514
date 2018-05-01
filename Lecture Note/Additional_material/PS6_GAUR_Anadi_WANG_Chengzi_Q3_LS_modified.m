% Binomial tree with 5000 step.
[StockPrice, OptionPrice] = binprice(100, 120, 0.06, 1, 1/100, 0.3, 0, 0.01, 0, 0);

% Longstaff and Schwartz method.
clear all

    path = 10000;
    r = 0.06;
    K = 120;
    d = 0.01;
    T = 1;
    sigma = 0.3;
    dt = T/12;
    S = zeros([path,13]);
    E1 = zeros([path,13]);
    R1 = zeros([path,13]);
    for j = 1:1:path
        S(j,1) = 100;
        for i = 2:13
            fi = normrnd(0,1);
            S(j,i) = S(j,i-1)*exp((r - d - 0.5*sigma^2)*dt + sigma*sqrt(dt)*fi);
            V1(j,i) = max(K - S(j,i), 0);
        end
    end

    for i = 12:-1:2
        X1 =[];
        Y = [];
        R1(:,13) = V1(:,13);
        for j = 1:1:path
            if S(j,i) < K
                X1 = [X1, S(j,i)];
                Y = [Y, exp(-r*dt)*R1(j,i+1)];
            end
        end
        b1 = polyfit(X1, Y, 3);
        CV1(:,i) = polyval(b1,S(:,i));
        for j = 1:path
            if CV1(j,i) >= V1(j,i)
                V1(j,i) = 0;
                R1(j,i) = exp(-r*dt)*R1(j,i+1);
            else
                V1(j,i+1:end) = 0;
                R1(j,i) = V1(j,i);
            %    E1(j,i) = exp(-r*(i-1)*dt);
             %   E1(j,i+1:end) = 0;
            end
        end
    end
    
    vec=[];
    for i = 0:1:12
    vec = [vec exp(-r*i*dt)];
    end
    vec= vec';
    
    American_put_option_LS= sum(V1*vec)/path
  
