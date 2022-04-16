library("lmtest")
library("GGally")
library("car")

data = na.omit(attitude) # insertion database exclude NA answers
      # rating- объясняемая переменная
      # {raises, critical, advance}- регрессоры

help(attitude)

model_1 = lm(rating ~ I(log(raises)) + I(log(advance)), data)
summary(model_1)

t_value = qt(0.975, df = 27)
t_value


new.data = data.frame(raises = 34, advance = 51)

predict(model_1, new.data, interval = "confidence")









