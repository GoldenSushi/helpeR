% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{cread_csv}
\alias{cread_csv}
\title{C Read}
\usage{
cread_csv(fileName, header)
}
\arguments{
\item{fileName}{name of the file or path leading to it.}

\item{header}{Indicates if the header is included in the file.}
}
\description{
Custom csv parser built using c++. For now it's just a test, and it is a little slower than R's read.csv, but in the future will have other custom utils
}
