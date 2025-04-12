create_comparison_table <- function(cData, javaData) {
  # Skriptet är nu gjort för bara tidsvärden.
  # Kan behöva formulera om datan här uppe om den är "1,234234" (med index)
  # Borde vi enbart ta java-resultat i jämviktsläget?
  tabell <- data.frame(
    "C+" = cData,
    "Java" = javaData,
    "Snabbast" = ifelse(cData < javaData, "C++", ifelse(javaData < cData, "Java", "Samma")),
    Skillnad = abs(cData - javaData)
  )

  print(tabell)

  return(tabell)
}

create_graph <- function(cData, javaData) {

data <- data.frame(
  Tidsindex = 1:length(varde1),   # x-axeln kan vara tid eller index
  Varde1 = cData,
  Varde2 = javaData
)

# types:
# l -> bara linje
# p -> bara punkt
# b -> both, linjer först (inte så clean)
# o -> punkt + linje, punkt över linje

plot(data$Tidsindex, data$Varde1, type="p", col="blue", pch=19, 
     xlab="Index", ylab="Tid", main="Jämförelse mellan två värden")
points(data$Tidsindex, data$Varde2, type="o", col="red", pch=19)
legend("topright", legend=c("C++", "Java"), col=c("blue", "red"), pch=19)
}

create_t_test <- function(cData, javaData) {
  jResultat <- t.test(javaData)
  jMean <- mean(javaData)
  cResultat <- t.test(cData)
  cMean <- mean(cData)
  
  print("T-test för Java:")
  print(jResultat)
  print("T-test för C++:")
  print(cResultat)
  
  # Jämför medelvärden
  diffMean <- jMean - cMean
  cat("Medelvärden:\n")
  cat("Java:", jMean, "\n")
  cat("C++:", cMean, "\n")
  cat("Skillnad (Java - C++):", diffMean, "\n")
}

