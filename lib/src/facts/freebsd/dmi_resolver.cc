#include <internal/facts/freebsd/dmi_resolver.hpp>
#include <leatherman/logging/logging.hpp>

#include <sys/sysctl.h>

using namespace std;

namespace facter { namespace facts { namespace freebsd {

    dmi_resolver::data dmi_resolver::collect_data(collection& facts)
    {
        data result;

        int cmd[2];
        size_t two = 2;
        sysctlnametomib("smbios.bios.vendor", cmd, &two);

        result.bios_vendor = sysctl_lookup(cmd);

        return result;
    }

    string dmi_resolver::sysctl_lookup(int mib_2)
    {
        int mib[2];
        size_t len;
        char value[BUFSIZ];

        mib[0] = CTL_HW;
        mib[1] = mib_2;
        len = sizeof(value) - 1;

        if (sysctl(mib, 2, &value, &len, nullptr, 0) == -1) {
            LOG_DEBUG("sysctl_lookup failed: %1% (%2%).", strerror(errno), errno);
            return "";
        }

        return value;
    }

} } }  // namespace facter::facts::freebsd
