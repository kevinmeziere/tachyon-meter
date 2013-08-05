/*
 *  kstat.hpp
 *
 *   Includes a nice library of functions 
 *   that allow easy interface with libkstat 
 *   from a C++ program.
 *
 *   CREATED:   5 AUG 2013
 *   EDITED:    5 AUG 2013
 */



extern bool VERBOSE;
extern bool VERBOSE2;



namespace KSTAT {




// Self-explanatory
uint64_t translate_to_ui64 (kstat_named_t *knp) {

  switch (knp->data_type) {
    case KSTAT_DATA_CHAR:
      std::cout << "WARN: Not coded yet." << std::endl;
      break;
    case KSTAT_DATA_INT32:
      return knp->value.i32;
    case KSTAT_DATA_UINT32:
      return (uint64_t)knp->value.ui32;
    case KSTAT_DATA_INT64:
      return (uint64_t)knp->value.i64;
    case KSTAT_DATA_UINT64:
      return (uint64_t)knp->value.ui64;
    default:
      // We should never end up in here
      std::cout << "Something rather peculiar happened @kstat.hpp:" << __LINE__ << std::endl;
      break;
    }

  return 0;
}


// Helper
void pv (std::vector<uint64_t> *v) {
  std::cout << "begin print\n";
  for (size_t i=0; i<v->size(); i++) {
    std::cout << v->at(i) << std::endl;
  }
}


/*
 * Allows the return of multiple values
 * in a vector.
 */
int retreive_multiple_kstat (kstat_ctl_t *kc, std::string module, std::string statistic, std::vector<uint64_t> *values) {
  values->clear();
  kstat_t         *ksp;
  kstat_named_t   *knp;

  ksp = kstat_lookup (kc, (char *)module.c_str(), -1, NULL);
  if (ksp == NULL) {
    std::cout << "Initial kstat lookup failed @kstat.hpp:";
    std::cout << __LINE__ << std::endl;
    return 1;
  }

  if (ksp->ks_type == KSTAT_TYPE_NAMED) {
    while (ksp != NULL) {
      kstat_read (kc, ksp, NULL);
      knp = (kstat_named_t *)kstat_data_lookup (ksp, (char *)statistic.c_str());
      if (knp == NULL) {
        std::cout << "Failed to resolve kstat statistic lookup @kstat.hpp:" << __LINE__ << std::endl;
        return 2;
      }

      if (VERBOSE) std::cout << "Retreived kstat from " << ksp->ks_module << " : " << ksp->ks_name << std::endl;
      
      values->push_back (translate_to_ui64 (knp));      

      ksp = kstat_lookup ((kstat_ctl_t *)(ksp->ks_next), (char *)module.c_str(), -1, NULL);
    }
  } 

  return 0;
}






























}


