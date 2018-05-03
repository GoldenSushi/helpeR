
#' Helper Read Table
#'
#' An user-friendly and simplified way to use the read.table function for the lazy and those are just beggining.
#' Keep in mind that only the parameters path and header are available in this function.
#'
#' @export
hread_table <- function() {
  print("your current dir is ")
  print(getwd())
  path1 = readline("Enter the path: ")
  print("Header true?\n[1] Yes\n[2] No\n[3] cancel")
  choice = readline("selection: ")
  header1 = FALSE
  if (choice == 1) header1 = TRUE
  if (choice == 3) stop()
  control = TRUE
  while (control){
    result <- tryCatch(read.table(file = path1, header = header1), error = function(e){return(1)}, warning = function(e){return(1)})
    if (inherits(result, "data.frame")){
      control = FALSE
    }else {
      print("Try again or press 1 to exit")
      path1 = readline("enter path or 1: ")
      if (path1 == 1) {
        control = FALSE
        result = "exiting..."
      }
    }
  }
  result
}