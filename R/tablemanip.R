#'Neural Arrange
#'
#'Organizes results from neural nework predictions. Creates a column and inserts in each row the name of the column with the biggest probability to occur. By the end, appends this columns to the inserted dataframe.
#'
#'@param x Data frame to be arranged
#'@export
neural.arrange <- function(x) {
  if (is.null(colnames(x)))
    print("Columns must have names. Please name your columns with 'colnames()' and try again.")
  else if (inherits(x, "data.frame")) {
    matConvert <- data.matrix(x)
    y <- .Call('_helpeR_neural_arrange', matConvert, PACKAGE = 'helpeR')
    cbind(y, x)
  }
  else
  y <- .Call('_helpeR_neural_arrange', x, PACKAGE = 'helpeR')
  cbind(y, x)
}